#pragma once
#include <raylib.h>

class Paddle {
private:
	int width;
	int height;
	int positionX;
	int positionY;
	int speed;

public:
	Paddle(int w, int h, int posX, int posY, int s);

		void setDimension(int w, int h);

		void setWidth(int w);

		void setHeight(int h);

		void setPosition(int x, int y);

		void setPositionX(int x);

		void setPositionY(int y);

		void setSpeed(int s);

		int getWidth();

		int getHeight();

		int getPositionX();

		int getPositionY();

		int getSpeed();

		Rectangle getRect();

		void Draw();

		void Move(KeyboardKey up, KeyboardKey down);

		void checkCollisionWithScreen();
};