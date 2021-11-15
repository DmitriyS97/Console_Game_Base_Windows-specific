#include"Arkanoid.h"

Ball::Ball()
{
	m_ballDir.x() = 1;
	m_ballDir.y() = -1;
}
void Ball::render(PaintDevice& paintDevice)
{
	paintDevice.set_char(m_Position, 0x2219);
}
void Ball::move()
{
	m_Position += m_ballDir;
}