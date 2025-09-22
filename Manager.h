#pragma once
#define MAX_OBJECTS 1000
using namespace System::Drawing;

class PopObject{
public:
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual void setPos(float x, float y) = 0;
	virtual int getSize() = 0;
	virtual void draw(Graphics^ graphics) = 0;
	virtual float getdX() = 0;
	virtual float getdY() = 0;
	virtual void setSpeed(float dX, float dY) = 0;
	virtual void move() = 0;
	virtual void interact(PopObject* popObject) = 0;
	virtual float getLastdX() = 0;
	virtual float getLastdY() = 0;

};

class Manager {
private:
	PopObject* _popObjects[MAX_OBJECTS];
	int _frameWidth, _frameHeight;
public:
	Manager(int frameWidth, int frameHeight);
	~Manager();
	void add(PopObject* popObject);
	void drawFrame(Graphics^ graphics);
	void move();
	bool remove(PopObject* popObject);
	PopObject* search(int x, int y);
	void setSpeedAll(float scale);
};

extern Manager* manager;