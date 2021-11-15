#include"Arkanoid.h"

Brick::Brick(size_t width, size_t height) : m_Width(width), m_Height(height)
{
	int start = width;
	int end = width;
	bool check = false;
	for (int i = 1; i < height - 11; i++)
	{
		for (int j = start / 2; j < end / 2; j++)
		{
			m_Bricks.push_back(Vector2(j, i));
			if (j <= 1) check = true;
		}
		if (check) {
			start += 2;
			end -= 2;
		}
		else {
			start -= 2;
			end += 2;
		}
	}	
}
bool Brick::hit(Vector2 point) {	
	for (const Vector2& enemy : m_Bricks) {
		if (enemy == point) {
			Brick::remove(point);
			return true;
		}
	}
	return false;
}

void Brick::remove(Vector2 point) {
	for (int i = 0; i < m_Bricks.size(); i++) {
		if (point == m_Bricks[i]) {
			std::swap(m_Bricks[i], m_Bricks.back());
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