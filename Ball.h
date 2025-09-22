#pragma once
#include "Manager.h"
using namespace System::Drawing;

class Ball : public PopObject
{
private:
	float _x, _y, _dX, _dY, _lastDX, _lastDY;
	int _color;
	int _borderColor;
	int _size;
	int _frameWidth, _frameHeight;

public:
	void draw(Graphics^ graphics);
	void setPos(float x, float y);
	Ball(int frameWidth, int frameHeight, float x, float y);
	void setColor(int color, int borderColor);
	int getSize();
	float getX();
	float getY();
	float getdX();
	float getdY();
	void setSpeed(float dX, float dY);
	void move();
	void interact(PopObject* popObject);
	float getLastdX();
	float getLastdY();

};

extern Ball* ball;