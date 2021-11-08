#include"Arkanoid.h"

void Ball::render(PaintDevice& paintDevice)
{
	paintDevice.set_char(m_Position, 0x2219);
}
void Ball::move(int x, int y)
{
	m_Position.x() += x;
	m_Position.y() += y;
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



Brick::Brick(size_t width, size_t height): m_Width(width), m_Height(height)
{	
	int start = width;
	int end = width;
	bool check = false;
	for (int i = 1; i < height -11; i++)
	{
		for (int j = start / 2; j < end / 2; j++)
		{
			m_Bricks.push_back(Vector2(j, i));
			if (j <= 1) check = true;
		}
		if (check == true) {
			start += 2;
			end -= 2;
		}
		else {
			start -= 2;
			end += 2;
		}
	}	
	/*for (int i = 1; i < width - 1; i++)
	{
		for (int j = 1; j < height / 2; j++)
		{
			m_Bricks.push_back(Vector2(i, j));
		}
	}*/
}
bool Brick::hit(Vector2 point) {

	for (const Vector2& enemy : m_Bricks) {
		if (enemy == point) {
			return true;
		}
	}
	return false;
}

void Brick::remove(Vector2 point) {
	for (int i = 0; i < m_Bricks.size(); i++) {
		if (point.x() == m_Bricks[i].x() && point.y() == m_Bricks[i].y()) {
			for (int j = i; j < m_Bricks.size() - 1; j++) {
				m_Bricks[j] = m_Bricks[j + 1];
			}
			m_Bricks.pop_back();
			return;
		}
	}
}

void Brick::render(PaintDevice& paintDevice) {
	for (const Vector2& point : m_Bricks) {
		paintDevice.set_char(point, 0x25A0);
	}
}



Wall::Wall(size_t width, size_t height) : m_Width(width), m_Height(height) {}

void Wall::render(PaintDevice& paintDevice)
{
	for (int y = 1; y < m_Height; y++) {
		paintDevice.set_char(Vector2(0, y), 0x2551);
		paintDevice.set_char(Vector2(m_Width-1, y), 0x2551);
	}
	for (int x = 1; x < m_Width-1; x++) {
		paintDevice.set_char(Vector2(x, 0), 0x2550);
	}
	paintDevice.set_char(Vector2(0, 0), 0x2554);
	paintDevice.set_char(Vector2(m_Width-1, 0), 0x2557);
}



void Arkanoid::render(PaintDevice& paintDevice) {
	m_Ball.render(paintDevice);
	m_Bricks.render(paintDevice);
	m_Platform.render(paintDevice);
	m_Walls.render(paintDevice);
}

void Arkanoid::update(const int dt)
{	
	m_Lag += dt;
	const int quant = 250;
	if (m_Lag <= quant) return;
	m_Lag -= quant;

	Vector2 directions;
	int x = m_Ball.m_xDir;
	int y = m_Ball.m_yDir;
	bool check = true;
	
	if (x == 1 && y == -1)								//Move Up Right
	{
		if (m_Ball.m_Position.x() + 1 == m_Width-1)		//Right Wall
		{
			x = -1;
			y = -1;
			
		}
		else if (m_Ball.m_Position.y() - 1 == 0)		//Ceiling
		{
			x = 1;
			y = 1;			
		}
		directions.x() = m_Ball.m_Position.x() + 1;
		if (m_Bricks.hit(directions))					//Right brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = -1;	
			check = false;
		}

		directions.x() = m_Ball.m_Position.x();
		directions.y() = m_Ball.m_Position.y() - 1;
		if (m_Bricks.hit(directions))					//Upper brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = 1;
			check = false;
		}
		
		directions.x() = m_Ball.m_Position.x() + 1;		
		if (m_Bricks.hit(directions) && check ==true)	//Right upper brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = 1;
		}

		
	}	
	else if (x == 1 && y == 1) // Down Right
	{
		for (int i = 0; i < m_Platform.m_Body.size(); i++) // To platform from right
		{
			if (m_Ball.m_Position.y() == m_Platform.m_Body[i].y() &&
				m_Ball.m_Position.x() == m_Platform.m_Body[i].x())
			{
				x = 1;
				y = -1;
				break;
			}
		}
		
		if (m_Ball.m_Position.x() + 1 == m_Width-1) //Right Wall
		{
			x = -1;
			y = 1;
		}

		directions.x() = m_Ball.m_Position.x() + 1;
		if (m_Bricks.hit(directions))					//Right brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = 1;		
			check = false;
		}
		directions.x() = m_Ball.m_Position.x();
		directions.y() = m_Ball.m_Position.y() + 1;
		if (m_Bricks.hit(directions))					//Down brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = -1;
			check = false;
		}
		directions.x() = m_Ball.m_Position.x() + 1;
		if (m_Bricks.hit(directions)&&check == true)	//Right Down brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = -1;
		}
	}
	else if (x == -1 && y == 1) // Down Left
	{
		for (int i = 0; i < m_Platform.m_Body.size(); i++) // To platform from left
		{
			if (m_Ball.m_Position.y() == m_Platform.m_Body[i].y() &&
				m_Ball.m_Position.x() == m_Platform.m_Body[i].x())
			{
				x = -1;
				y = -1;
				break;
			}
		}
		if (m_Ball.m_Position.x() - 1 == 0) // Left Wall
		{
			x = 1;
			y = 1;
		}
		
		directions.x() = m_Ball.m_Position.x() - 1;
		if (m_Bricks.hit(directions))					//Left brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = 1;
			check = false;
		}
		directions.x() = m_Ball.m_Position.x();
		directions.y() = m_Ball.m_Position.y() + 1;
		if (m_Bricks.hit(directions))					//Down brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = -1;
			check = false;
		}
		directions.x() = m_Ball.m_Position.x() - 1;
		if (m_Bricks.hit(directions) && check == true)	//Left Down brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = -1;
		}
	}
	else if (x == -1 && y == -1) // Up Left
	{
		if (m_Ball.m_Position.x() - 1 == 0) // Left Wall
		{
			x = 1;
			y = -1;
		}
		else if (m_Ball.m_Position.y() - 1 == 0) // Ceiling
		{
			x = -1;
			y = 1;
		}
		directions.x() = m_Ball.m_Position.x() - 1;
		if (m_Bricks.hit(directions))					//Left  brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = -1;
			check = false;
		}
		directions.x() = m_Ball.m_Position.x();
		directions.y() = m_Ball.m_Position.y() - 1;
		if (m_Bricks.hit(directions))					//Upper brick
		{
			m_Bricks.remove(directions);
			x = -1;
			y = 1;
			check = false;
		}
		directions.x() = m_Ball.m_Position.x() - 1;
		if (m_Bricks.hit(directions) && check == true)	//Left Upper brick
		{
			m_Bricks.remove(directions);
			x = 1;
			y = 1;
		}
	}

	m_Ball.move(x, y);
	m_Ball.m_xDir = x;
	m_Ball.m_yDir = y;
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
	m_Ball.m_Position=Vector2(m_Width/2, m_Height - 3);
}