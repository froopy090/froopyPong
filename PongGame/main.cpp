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
#define BALL_POSITION_OFFSET 200

//paddle constants
#define PAD_WIDTH 5
#define PAD_HEIGHT 100
#define PADDING 60
#define PAD_SPEED 500

typedef enum GameScreen {LOGO = 0, TITLE, GAMEPLAY, GAMEOVER1, GAMEOVER2} GameScreen; //going to use this to separate the different screens

int main() {
	//creating a window
	InitWindow(DIM_WIDTH, DIM_WIDTH, "froopyPong");
	SetWindowState(FLAG_VSYNC_HINT); //VSYNCs my window so I don't get 3000+ fps lol

	//initializing ball and paddles
	Ball ball(RADIUS, GetScreenWidth() / 2 - BALL_POSITION_OFFSET, GetScreenHeight() / 2, VELOCITY_X, VELOCITY_Y);

	int paddleRightPosX = GetScreenWidth() - (PADDING + PAD_WIDTH); //i did + width cos the origin of the rectangle is at the top right corner
	int paddlePosY = GetScreenHeight() / 2 - PAD_HEIGHT / 2; //so i need to consider the padding and also the width
	Paddle paddleRight(PAD_WIDTH, PAD_HEIGHT, paddleRightPosX, paddlePosY, PAD_SPEED);

	int paddleLeftPosX = PADDING;
	Paddle paddleLeft(PAD_WIDTH, PAD_HEIGHT, paddleLeftPosX, paddlePosY, PAD_SPEED);


	//initializing other variables
	GameScreen currentScreen = LOGO;
	int framesCounter = 0;
	SetTargetFPS(144); //frames will be useful to measure how long in seconds I want certain screens to show up for

	int winState = 0;
	int bigFontSize = 50;
	int smallFontSize = 20;

	const char logoText[] = "FROOP STUDIOS";
	const char titleText[] = "FROOPY PONG EPIC";
	const char pressSpaceText1[] = "Press SPACE to start";
	const char pressSpaceText2[] = "Press SPACE to return to TITLE";
	const char winTextRight[] = "Right Player Wins!";
	const char winTextLeft[] = "Left Player Wins!";

	float velocityMultiplier = -1.05;


	while (!WindowShouldClose()) { //basically this runs when my window isn't supposed to close

		//Screen update
		//--------------------------------------------------------------------------------------------------
		switch (currentScreen)
		{
		case LOGO: {
			framesCounter++; //count the frames

			//after two seconds go to title screen (2s = 288 frames)
			if (framesCounter > 288) {
				currentScreen = TITLE;
			}
		}
			break;
		case TITLE: {
			if (IsKeyPressed(KEY_SPACE)) { //press space to start the game
				currentScreen = GAMEPLAY;
			}
		}
			break;
		case GAMEPLAY: {
			if (ball.checkWinLeft()) {
				currentScreen = GAMEOVER1;
			}
			if (ball.checkWinRight()) {
				currentScreen = GAMEOVER2;
			}
		}
			break;
		case GAMEOVER1: {
			if (IsKeyPressed(KEY_SPACE)) { //press space to start a new game
				currentScreen = TITLE;
			}
		}
			break;
		case GAMEOVER2: {
			if (IsKeyPressed(KEY_SPACE)) { //press space to start a new game
				currentScreen = TITLE;
			}
		}
		default:
			break;
		}
		//-----------------------------------------------------------------------------------------------------------------------------



		//Drawing
		//-----------------------------------------------------------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(BLACK); //black background
			DrawFPS(10,10); //shows fps

			switch (currentScreen)
			{
			case LOGO: {
				DrawText(logoText, GetScreenWidth() / 2 - MeasureText(logoText, bigFontSize) / 2, GetScreenHeight() / 2, bigFontSize, YELLOW);
			}
				break;
			case TITLE: {
				DrawText(titleText, GetScreenWidth() / 2 - MeasureText(titleText, bigFontSize) / 2, GetScreenHeight() / 2 - 300, bigFontSize, YELLOW);
				DrawText(pressSpaceText1, GetScreenWidth() / 2 - MeasureText(pressSpaceText1, smallFontSize) / 2, GetScreenHeight() / 2 - 200, smallFontSize, YELLOW);

				//drawing shapes here as well so that players can already see the starting position of the ball
				ball.Draw();
				paddleRight.Draw();
				paddleLeft.Draw();
			}
				break;
			case GAMEPLAY: {
				//drawing shapes
				ball.Draw();
				paddleRight.Draw();
				paddleLeft.Draw();

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
					//this extra if makes it so that if the ball hits the top of the paddle, it goes up, and if it hits the bottom it goes down
					if (ball.getPositionY() > paddleLeft.getPositionY() + (paddleLeft.getHeight() /2)) {
						ball.setVelocityY(VELOCITY_Y);
					}
					else {
						ball.setVelocityY(VELOCITY_Y * -1);
					}
				}
				//right paddle
				if (CheckCollisionCircleRec(ball.getVector2Center(), ball.getRadius(), paddleRight.getRect()) && ball.getVelocityX() > 0) {
					ball.setVelocityX(ball.getVelocityX() * velocityMultiplier); //making the ball a bit faster with each hit
					if (ball.getPositionY() > paddleRight.getPositionY() + (paddleRight.getHeight() / 2)) {
						ball.setVelocityY(VELOCITY_Y);
					}
					else {
						ball.setVelocityY(VELOCITY_Y * -1);
					}
				}
			}
				break;
			case GAMEOVER1: {
				DrawText(winTextLeft, GetScreenWidth() / 2 - (MeasureText(winTextLeft, 50) / 2), GetScreenHeight() / 2, 50, YELLOW);
				DrawText(pressSpaceText2, GetScreenWidth() / 2 - MeasureText(pressSpaceText2, 20) / 2, GetScreenHeight() / 2 + 100, 20, YELLOW);
				ball.setPosition(GetScreenWidth() / 2 - BALL_POSITION_OFFSET, GetScreenHeight() / 2); //reseting the ball
				ball.setVelocity(VELOCITY_X, VELOCITY_Y);
				paddleLeft.setPosition(paddleLeftPosX, paddlePosY); //reseting the paddles
				paddleRight.setPosition(paddleRightPosX, paddlePosY);
			}
				break;
			case GAMEOVER2: {
				DrawText(winTextRight, GetScreenWidth() / 2 - (MeasureText(winTextLeft, 50) / 2), GetScreenHeight() / 2, 50, YELLOW);
				DrawText(pressSpaceText2, GetScreenWidth() / 2 - MeasureText(pressSpaceText2, 20) / 2, GetScreenHeight() / 2 + 100, 20, YELLOW);
				ball.setPosition(GetScreenWidth() / 2 + BALL_POSITION_OFFSET, GetScreenHeight() / 2); //reseting the ball
				ball.setVelocity(VELOCITY_X * -1, VELOCITY_Y);
				paddleLeft.setPosition(paddleLeftPosX, paddlePosY); //reseting the paddles
				paddleRight.setPosition(paddleRightPosX, paddlePosY);
			}
			default:
				break;
			}
		EndDrawing(); //always include this
	}

	CloseWindow(); //always include this
	return 0;
}