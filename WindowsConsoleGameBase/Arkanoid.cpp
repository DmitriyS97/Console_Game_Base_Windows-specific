#include"Arkanoid.h"

void Arkanoid::render(PaintDevice& paintDevice) {	
	m_Bricks.render(paintDevice);	
	m_Walls.render(paintDevice);
	m_Ball.render(paintDevice);
	m_Platform.render(paintDevice);
}

void Arkanoid::update(const int dt)
{	
	m_Lag += dt;
	const int quant = 150;
	if (m_Lag <= quant) return;
	m_Lag -= quant;	

	Vector2 ballPos(m_Ball.m_xDir, m_Ball.m_yDir);

	if ((m_Ball.m_Position.x() - 1 == 0 && m_Ball.m_Position.y() - 1 == 0)
		|| (m_Ball.m_Position.x() + 1 == m_Width - 1 && m_Ball.m_Position.y() - 1 == 0))
	{
		m_Ball.m_xDir *= -1;
		m_Ball.m_yDir *= -1;
	}
	else if (m_Ball.m_Position.x() + 1 == m_Width - 1 || m_Ball.m_Position.x() - 1 == 0) m_Ball.m_xDir *= -1;
	else if (m_Ball.m_Position.y()+1 == m_Height || m_Ball.m_Position.y() - 1 == 0) m_Ball.m_yDir *= -1;
	
	if (m_Platform.hit(m_Ball.m_Position + ballPos)) m_Ball.m_yDir *= -1;

	bool check = true;
	
	if (m_Bricks.hit(m_Ball.m_Position + Vector2(-1, 0)) || m_Bricks.hit(m_Ball.m_Position + Vector2(1, 0)))
	{
		m_Ball.m_xDir *= -1;
		check = false;
	}
	if (m_Bricks.hit(m_Ball.m_Position + Vector2(0,-1)) || m_Bricks.hit(m_Ball.m_Position + Vector2(0, 1)))  
	{
		m_Ball.m_yDir *= -1;
		check = false;
	}
	if (check == true && (m_Bricks.hit(m_Ball.m_Position + ballPos)))
	{
		m_Ball.m_xDir *= -1;
		m_Ball.m_yDir *= -1;
	}

	m_Ball.move();
	
}

void Arkanoid::on_button_press(const int button) {
	switch (button)
	{
	case VK_LEFT:
	{
		m_Platform.m_Position.x()--;
		if (m_Platform.m_Position.x() < 0) m_Platform.m_Position.x() = 0;
		break;
	}

	case VK_RIGHT:
	{
		m_Platform.m_Position.x()++;
		if (m_Platform.m_Position.x() > m_Width - 7) m_Platform.m_Position.x() = m_Width - 7;
		break;
	}

	default:
		break;
	}
}

Arkanoid::Arkanoid(): m_Walls(m_Width,m_Height), m_Bricks(m_Width, m_Height) {
	
	paint_device().resize(Size(m_Width, m_Height));
	track_key(VK_LEFT);
	track_key(VK_RIGHT);	
	m_Platform.m_Position = Vector2(m_Width/2-3, m_Height-2);
	m_Ball.m_Position=Vector2(m_Width/2, m_Height - 4);
}