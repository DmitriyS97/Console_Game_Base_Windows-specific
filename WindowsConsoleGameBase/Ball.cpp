#include"Arkanoid.h"

void Ball::render(PaintDevice& paintDevice)
{
	paintDevice.set_char(m_Position, 0x2219);
}
void Ball::move()
{
	m_Position.x() += m_xDir;
	m_Position.y() += m_yDir;
}