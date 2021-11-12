#include"Arkanoid.h"

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
		paintDevice.set_char(m_Position + point, 0x2550);
	}
}

bool Platform::hit(Vector2 point) {

	for (const Vector2& body : m_Body) {
		if (m_Position + body == point) {
			return true;
		}
	}
	return false;
}