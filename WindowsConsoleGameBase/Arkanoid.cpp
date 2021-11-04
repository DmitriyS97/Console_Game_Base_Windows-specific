#include"Arkanoid.h"

void Ball::render(PaintDevice& paintDevice)
{
	paintDevice.set_char(m_Position, 0x2219);
}

void Ball::update(const int dt) {
	m_Lag += dt;
	const int quant = 50;
	if (m_Lag <= quant) return;
	m_Lag -= quant;
}

 

Platform::Platform()
{
	m_Body = {
		Vector2(1, 0),
		Vector2(2, 0),
		Vector2(3, 0),
		Vector2(4, 0),
		Vector2(5, 0),
	};
}

void Platform::render(PaintDevice& paintDevice) {
	for (const Vector2& point : m_Body) {
		paintDevice.set_char(Vector2(m_Position.x() + point.x(), m_Position.y() + point.y()), 0x2550);
	}
}



Brick::Brick()
{
	for (int i = 1; i < 29; ++i) {
		for (int j = 1; j < 25; j++)
		{
			if (rand() % 2) 
			{
				m_Bricks.push_back(Vector2(i, j));
			}
		}
	}
}

void Brick::render(PaintDevice& paintDevice) {
	for (const Vector2& point : m_Bricks) {
		paintDevice.set_char(point, 0x25A0);
	}
}

void Brick::update(const int dt) {
	m_Lag += dt;
	const int quant = 800;
	if (m_Lag <= quant) return;
	m_Lag -= quant;
}



Wall::Wall()
{
	for (int i = 0; i <= 30; ++i) {
		for (int j = 0; j < 40; j++)
		{
			if (i==0  || i==29 || j==0)
			m_Walls.push_back(Vector2(i, j));
		}
	}
}

void Wall::render(PaintDevice& paintDevice)
{
	for (const Vector2& point : m_Walls) {
		paintDevice.set_char(point, 0x2588);
	}
}



void Arkanoid::render(PaintDevice& paintDevice) {
	m_Ball.render(paintDevice);
	m_Bricks.render(paintDevice);
	m_Platform.render(paintDevice);
	m_Walls.render(paintDevice);
}

void Arkanoid::update(const int dt)
{
	m_Ball.update(dt);
	m_Bricks.update(dt);	
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

Arkanoid::Arkanoid() {
	paint_device().resize(Size(m_Width, m_Height));
	track_key(VK_LEFT);
	track_key(VK_RIGHT);

	m_Platform.m_Position = Vector2(m_Width/2-3, m_Height-2);
	m_Ball.m_Position=Vector2(m_Width/2, m_Height - 3);
}