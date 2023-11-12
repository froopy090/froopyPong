#include "Paddle.h"
#include <raylib.h>

	Paddle::Paddle(int w, int h, int posX, int posY, int s) {
		this->width = w;
		this->height = h;
		this->positionX = posX;
		this->positionY = posY;
		this->speed = s;
	}
	void Paddle::setDimension(int w, int h) {
		this->width = w;
		this->height = h;
	}
	void Paddle::setWidth(int w) {
		this->width = w;
	}

	void Paddle::setHeight(int h) {
		this->height = h;
	}

	void Paddle::setPosition(int x, int y) {
		this->positionX = x;
		this->positionY = y;
	}

	void Paddle::setPositionX(int x) {
		this->positionX = x;
	}

	void Paddle::setPositionY(int y) {
		this->positionY = y;
	}

	void Paddle::setSpeed(int s) {
		this->speed = s;
	}

	int Paddle::getWidth() {
		return width;
	}

	int Paddle::getHeight() {
		return height;
	}

	int Paddle::getPositionX() {
		return positionX;
	}

	int Paddle::getPositionY() {
		return positionY;
	}

	int Paddle::getSpeed() {
		return speed;
	}

	//returns a Rectangle struct with the position and dimensions of the paddle
	Rectangle Paddle::getRect() {
		Rectangle rec;
		rec.width = width;
		rec.height = height;
		rec.x = positionX;
		rec.y = positionY;

		return rec;
	}

	//draws the paddle in the window in WHITE
	void Paddle::Draw() {
		DrawRectangleRec(getRect(), WHITE);
	}

	//specify the keys for which you'd like the paddle to move up and down with
	void Paddle::Move(KeyboardKey up, KeyboardKey down) {
		if (IsKeyDown(up)) {
			this->positionY -= this->speed * GetFrameTime();
		}
		if (IsKeyDown(down)) {
			this->positionY += this->speed * GetFrameTime();
		}
	}

	//stops the paddle from going outside of the window
	void Paddle::checkCollisionWithScreen() {
		if (this->positionY < 0) {
			this->positionY = 0.0;
		}
		if (this->positionY + this->height > GetScreenHeight()) {
			this->positionY = GetScreenHeight() - this->height;
		}
	}