#pragma once
#include <raylib.h>
class Ball {
private:
	float radius;
	float positionX;
	float positionY;
	float velocityX;
	float velocityY;

public:
	Ball(float r, float posX, float posY, float velX, float velY);

	void setRadius(float r);

	void setPosition(float x, float y);

	void setPositionX(float x);

	void setPositionY(float y);

	void setVelocity(float x, float y);

	void setVelocityX(float x);

	void setVelocityY(float y);

	float getRadius();

	int getPositionX();

	int getPositionY();

	int getVelocityX();

	int getVelocityY();

	void Move();

	void Draw();

	Vector2 getVector2Center();

	void checkCollisionWithScreen();
};