#pragma once
#include"Engine.h"
#include<vector>


class Ball
{
public:	
	void render(PaintDevice& paintDevice);	
	void move(int x,int y);
	Vector2 m_Position;	
	int m_xDir = 1;
	int m_yDir = -1;	
};

class Platform
{
public:
	Platform();
	void render(PaintDevice& paintDevice);
	Vector2 m_Position;
	std::vector<Vector2> m_Body;
};

class Brick
{
public:
	Brick(size_t width, size_t height);
	void render(PaintDevice& paintDevice);
	bool hit(Vector2 point);
	void remove(Vector2 point);
	bool empty() const { return m_Bricks.empty(); }
private:
	const size_t m_Width;
	const size_t m_Height;
	std::vector<Vector2> m_Bricks;
};
class Wall
{
public:
	Wall(size_t width, size_t height);
	
	void render(PaintDevice& paintDevice);
private:
	
	const size_t m_Width;
	const size_t m_Height;
};

class Arkanoid : public Engine
{
public:
	Arkanoid();	
	
private:
	virtual bool end() const { return !m_Bricks.empty() && m_Ball.m_Position.y() >= m_Height; } 
	virtual void on_button_press(const int button);
	virtual void update(const int dt);
	virtual void render(PaintDevice& paintDevice);	
	int m_Lag = 0;

	const size_t m_Width = 30;
	const size_t m_Height = 40;

	Platform m_Platform;
	Ball m_Ball;
	Brick m_Bricks;
	Wall m_Walls;	
};
