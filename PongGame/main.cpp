#include <raylib.h>
#include "Ball.h"
#include "Paddle.h"

//window dimensions
#define DIM_WIDTH 800
#define DIM_HEIGHT 600

//ball constants
#define RADIUS 5.0
#define VELOCITY_X 300
#define VELOCITY_Y 300

//paddle constants
#define PAD_WIDTH 5
#define PAD_HEIGHT 100
#define PADDING 60
#define PAD_SPEED 500

int main() {
	//creating a window
	InitWindow(DIM_WIDTH, DIM_WIDTH, "Pong");
	SetWindowState(FLAG_VSYNC_HINT); //VSYNCs my window so I don't get 3000+ fps lol

	//initializing ball and paddles
	Ball ball(RADIUS, GetScreenWidth() / 2, GetScreenHeight() / 2, VELOCITY_X, VELOCITY_Y);

	int paddleRightPosX = GetScreenWidth() - (PADDING + PAD_WIDTH); //i did + width cos the origin of the rectangle is at the top right corner
	int paddlePosY = GetScreenHeight() / 2 - PAD_HEIGHT / 2; //so i need to consider the padding and also the width
	Paddle paddleRight(PAD_WIDTH, PAD_HEIGHT, paddleRightPosX, paddlePosY, PAD_SPEED);

	int paddleLeftPosX = PADDING;
	Paddle paddleLeft(PAD_WIDTH, PAD_HEIGHT, paddleLeftPosX, paddlePosY, PAD_SPEED);


	const char winTextRight[] = "Right Player Wins!";
	const char winTextLeft[] = "Left Player Wins!";

	int randomNum1 = 1;
	int randomNum2 = 1;
	float velocityMultiplier = -1.05;

	while (!WindowShouldClose()) { //basically this runs when my window isn't supposed to close

		//ball movement
		ball.Move();

		//paddle movement, keyboard controls
		paddleRight.Move(KEY_UP, KEY_DOWN);
		paddleLeft.Move(KEY_W, KEY_S);

		//restricting paddle movement to window border
		paddleLeft.checkCollisionWithScreen();
		paddleRight.checkCollisionWithScreen();

		//ball collision with window border
		ball.checkCollisionWithScreen();

		//ball collision with paddles
		//left paddle
		if (CheckCollisionCircleRec(ball.getVector2Center(), ball.getRadius(), paddleLeft.getRect()) && ball.getVelocityX() < 0) {
			//the && fixes bug where ball gets stuck on paddle
			ball.setVelocityX(ball.getVelocityX() * velocityMultiplier); //basically I only switch directions when the ball is going to the left
		}
		//right paddle
		if (CheckCollisionCircleRec(ball.getVector2Center(), ball.getRadius(), paddleRight.getRect()) && ball.getVelocityX() > 0) {
			ball.setVelocityX(ball.getVelocityX() * velocityMultiplier); //making the ball a bit faster with each hit
		}

		//restart the game
		if (ball.getVelocityX() == 0 && ball.getVelocityY() == 0 && IsKeyPressed(KEY_SPACE)) {
			ball.setPosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

			do {
				randomNum1 = GetRandomValue(-1, 1);
				randomNum2 = GetRandomValue(-1, 1);
			} while (randomNum1 == 0 || randomNum2 == 0); //excluding 0 from my random number range

			ball.setVelocityX(VELOCITY_X * randomNum1);
			ball.setVelocityY(VELOCITY_Y * randomNum2);
		}


		BeginDrawing();
			ClearBackground(BLACK); //black background
			DrawFPS(10,10); //shows fps

			//drawing shapes
			ball.Draw();
			paddleRight.Draw();
			paddleLeft.Draw();

			//win condition
			if (ball.getPositionX() >= GetScreenWidth()) {
				DrawText(winTextLeft, GetScreenWidth() / 2 - (MeasureText(winTextLeft, 30) / 2), GetScreenHeight() / 2, 30, YELLOW);
				ball.setVelocity(0, 0);
			}
			if (ball.getPositionX() <= 0) {
				DrawText(winTextRight, GetScreenWidth() / 2 - (MeasureText(winTextLeft, 30) / 2), GetScreenHeight() / 2, 30, YELLOW);
				ball.setVelocity(0, 0);
			}

		EndDrawing(); //always include this
	}

	CloseWindow(); //always include this
	return 0;
}