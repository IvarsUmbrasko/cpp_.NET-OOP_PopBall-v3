#include "Ball.h"
#include <math.h>
#include <cstdlib>

using namespace System;
using namespace System::Drawing;

Ball* ball;

void Ball::draw(Graphics^ graphics) {
	SolidBrush brush(Color::FromArgb(_color));
	Pen pen(Color::FromArgb(_borderColor), 4);
	graphics->FillEllipse(% brush, (int)(_x - _size / 2), (int)(_y - _size / 2), _size, _size);
	graphics->DrawEllipse(% pen, (int)(_x - _size / 2), (int)(_y - _size / 2), _size, _size);
}

void Ball::setPos(float x, float y) {
	if (_size / 2 > x) x = _size / 2;
	if (x > _frameWidth - _size / 2) x = _frameWidth - _size / 2;
	if (_size / 2 > y) y = _size / 2;
	if (y > _frameHeight - _size / 2) y = _frameHeight - _size / 2;

	_x = x;
	_y = y;
}

Ball::Ball(int frameWidth, int frameHeight, float x, float y) {
	_x = x;
	_y = y;
	_size = 40;
	_color = Color::FromArgb(rand() % 256, rand() % 256, rand() % 256).ToArgb();
	_borderColor = Color::FromArgb(rand() % 256, rand() % 256, rand() % 256).ToArgb();
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	do {
		_dX = (rand() % 21) - 10;
		_dY = (rand() % 21) - 10;
	} while (_dX == 0 && _dY == 0);
}

void Ball::setColor(int color, int borderColor) {
	_color = color;
	_borderColor = borderColor;
}

int Ball::getSize() {
	return _size / 2;
}

float Ball::getX() {
	return _x;
}

float Ball::getY() {
	return _y;
}

float Ball::getdX() {
	return _dX;
}

float Ball::getdY() {
	return _dY;
}

void Ball::setSpeed(float dX, float dY) {
	float speed = sqrt(dX * dX + dY * dY);
	float angle = atan2(dY, dX);

	if (speed < 50 && speed > 1) {
		_dX = speed * cos(angle);
		_dY = speed * sin(angle);
		_lastDX = _dX;
		_lastDY = _dY;
	}

	if (fabs(speed) < 1) { speed = 0; _dX = 0, _dY = 0; }
}

void Ball::move() {
	_x += getdX();
	_y += getdY();

	if (_x - _size / 2 < 0 || _x + _size / 2 > _frameWidth) {
		_dX = -_dX;
		_x += _dX;
	}
	if (_y - _size / 2 < 0 || _y + _size / 2 > _frameHeight) {
		_dY = -_dY;
		_y += _dY;
	}
}

void Ball::interact(PopObject* popObject) {
	_dX = -_dX;
	_dY = -_dY;
}

float Ball::getLastdX() {
	return _lastDX;
}

float Ball::getLastdY() {
	return _lastDY;
}

