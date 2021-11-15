#include"Arkanoid.h"

Wall::Wall(size_t width, size_t height) : m_Width(width), m_Height(height) {}

void Wall::render(PaintDevice& paintDevice)
{
	for (int y = 1; y < m_Height; y++) {
		paintDevice.set_char(Vector2(0, y), 0x2551);
		paintDevice.set_char(Vector2(m_Width - 1, y), 0x2551);
	}
	for (int x = 1; x < m_Width - 1; x++) {
		paintDevice.set_char(Vector2(x, 0), 0x2550);
	}
	paintDevice.set_char(Vector2(0, 0), 0x2554);
	paintDevice.set_char(Vector2(m_Width - 1, 0), 0x2557);
}
