#include "Manager.h"
#include "math.h"

Manager* manager;

Manager::Manager(int frameWidth, int frameHeight) {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		_popObjects[i] = nullptr;
	}
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
}

Manager::~Manager() {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		_popObjects[i] = nullptr;
	}
}

void Manager::drawFrame(Graphics^ graphics) {
	Pen pen(Color::Black, 5);
	graphics->FillRectangle(% SolidBrush(Color::White), 0, 0, _frameWidth, _frameHeight);
	graphics->DrawRectangle(% pen, 0, 0, _frameWidth, _frameHeight);
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (_popObjects[i]) {
			_popObjects[i]->draw(graphics);
		}
	}
}

void Manager::add(PopObject* popObject) {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (!_popObjects[i]) {
			_popObjects[i] = popObject;
			break;
		}
	}
}

bool Manager::remove(PopObject* popObject) {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (_popObjects[i] == popObject) {
			_popObjects[i] = nullptr;
			delete popObject;
			return true;
			break;
		}
	}
}

void Manager::move() {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (_popObjects[i] != nullptr) {
			_popObjects[i]->move();
			float x1 = _popObjects[i]->getX();
			float y1 = _popObjects[i]->getY();
			int radius1 = _popObjects[i]->getSize();
			for (int j = i + 1; j < MAX_OBJECTS; ++j) {
				if (_popObjects[j] != nullptr) {
					float x2 = _popObjects[j]->getX();
					float y2 = _popObjects[j]->getY();
					int radius2 = _popObjects[j]->getSize();
					float dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					if (dist < radius1 + radius2) {
						_popObjects[i]->interact(_popObjects[j]);
						_popObjects[j]->interact(_popObjects[i]);
					}
				}
			}
		}
	}
}

PopObject* Manager::search(int x, int y) {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (_popObjects[i] != nullptr) {
			float x1 = _popObjects[i]->getX();
			float y1 = _popObjects[i]->getY();
			int radius = _popObjects[i]->getSize();
			float dist = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
			if (dist < radius) {
				return _popObjects[i];
			}
		}
	}
	return nullptr;
}

void Manager::setSpeedAll(float scale) {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (_popObjects[i] != nullptr) {

			float dX = _popObjects[i]->getdX();
			float dY = _popObjects[i]->getdY();
			if (dX == 0 && dY == 0 && scale > 1) {
				float lastDX = _popObjects[i]->getLastdX();
				float lastDY = _popObjects[i]->getLastdY();
				_popObjects[i]->setSpeed(lastDX * scale, lastDY * scale);
			}
			else {
				_popObjects[i]->setSpeed(dX * scale, dY * scale);
			}
		}
	}
}
