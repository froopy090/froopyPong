#include "Ball.h"
#include <raylib.h>


	Ball::Ball(float r, float posX, float posY, float velX, float velY) {
		radius = r;
		positionX = posX;
		positionY = posY;
		velocityX = velX;
		velocityY = velY;
	}

	void Ball::setRadius(float r) {
		this->radius = r;
	}

	void Ball::setPosition(float x, float y) {
		this->positionX = x;
		this->positionY = y;
	}

	void Ball::setPositionX(float x) {
		this->positionX = x;
	}

	void Ball::setPositionY(float y) {
		this->positionY = y;
	}

	void Ball::setVelocity(float x, float y) {
		this->velocityX = x;
		this->velocityY = y;
	}

	void Ball::setVelocityX(float x) {
		this->velocityX = x;
	}

	void Ball::setVelocityY(float y) {
		this->velocityY = y;
	}

	float Ball::getRadius() {
		return radius;
	}

	int Ball::getPositionX() {
		return positionX;
	}

	int Ball::getPositionY() {
		return positionY;
	}

	int Ball::getVelocityX() {
		return velocityX;
	}

	int Ball::getVelocityY() {
		return velocityY;
	}

	//changes the ball's x and y position
	void Ball::Move() {
		this->positionX += this->velocityX * GetFrameTime();
		this->positionY += this->velocityY * GetFrameTime();
	}

	//draws the ball in the window at (x,y) in WHITE
	void Ball::Draw() {
		DrawCircle(positionX, positionY, radius, WHITE);
	}

	//returns a vector2 struct with the center coordinates of the ball
	Vector2 Ball::getVector2Center() {
		Vector2 center = { positionX, positionY };
		return center;
	}

	//stops the ball from going outside of the window
	void Ball::checkCollisionWithScreen() {
		if (this->positionX > GetScreenWidth()) {
			this->positionX = GetScreenWidth(); //makes sure the ball doesn't get stuck on the edge of the screen
			this->velocityX *= -1; //reverses direction
		}
		if (this->positionX < 0) {
			this->positionX = 0;
			this->velocityX *= -1;
		}
		if (this->positionY > GetScreenHeight()) {
			this->positionY = GetScreenHeight();
			this->velocityY *= -1;
		}
		if (this->positionY < 0) {
			this->positionY = 0;
			this->velocityY *= -1;
		}
	}