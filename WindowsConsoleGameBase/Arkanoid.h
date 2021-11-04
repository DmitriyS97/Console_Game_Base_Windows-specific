#pragma once
#include"Engine.h"
#include<vector>

class Ball
{
public:	
	void render(PaintDevice& paintDevice);
	void update(const int dt);

	Vector2 m_Position;	
	int m_Lag = 0;
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
	Brick();
	void render(PaintDevice& paintDevice);
	void update(const int dt);
	int m_Lag = 0;
	//bool hit(Vector2 point);
	//void remove(Vector2 point);
	Vector2 first() const { return m_Bricks.front(); }
	bool empty() const { return m_Bricks.empty(); }
private:
	std::vector<Vector2> m_Bricks;
};
class Wall
{
public:
	Wall();
	void render(PaintDevice& paintDevice);
private:
	std::vector<Vector2> m_Walls;
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

	const size_t m_Width = 30;
	const size_t m_Height = 40;
	Platform m_Platform;
	Ball m_Ball;
	Brick m_Bricks;
	Wall m_Walls;
};
