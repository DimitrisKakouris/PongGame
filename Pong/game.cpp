#include "game.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include <iostream>
#include "difficulty.h"

bool hard = false;
bool medium = false;
bool easy = false;
bool usererror = false;

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
	else {
		updateEndingScreen();
	}

}

void Game::draw()
{
	if (status == STATUS_START)
	{

		drawStartScreen();

	}
	else if (status == STATUS_PLAYING){
		drawLevelScreen();
	}
	else {
		drawEndingScreen();
	}

}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "bitstream.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "homescreen.mp3", 1.0f, false, 0);
	

}


void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)&&  usererror)
	{
		status = STATUS_PLAYING;
		
	}


	graphics::MouseState ms;
	graphics::getMouseState(ms);
	
	if (ms.button_left_pressed && usererror)
	{
		status = STATUS_PLAYING;
	}

}

void Game::updateLevelScreen()
{

	if (hard) {
		difficulty1::foo(3);
	}
	else if (medium) {
		difficulty1::foo(2);
	}
	else
		difficulty1::foo(1);

	//Create players
	if (!player_initiallized && graphics::getGlobalTime() > 100) {

		player = new Player(*this);
		player2 = new Player(*this);
		player_initiallized = true;

		player->setPosX(50);
		player->setPosY(10);

		player2->setPosX(50);
		player2->setPosY(CANVAS_WIDTH - 10);

		if (hard) {
			player->setWidth(10);
			player->setHeight(30);
			player2->setWidth(10);
			player2->setHeight(30);

		}
		if (medium) {
			player->setWidth(10);
			player->setHeight(50);
			player2->setWidth(10);
			player2->setHeight(50);

		}
		if (easy) {
			player->setWidth(10);
			player->setHeight(100);
			player2->setWidth(10);
			player2->setHeight(100);

		}
	}


	if (player || player2) {
		updateKeys();
	}
	if (ball)
		ball->update();

	spawnball();
	chechball();
	spawnPowerup();


	//chech if collicion is true and changes direction of ball
	if (checkCollicion())
	{
		ball->ChangesDirection();
		ball->setCollisionWithPlayer(true);
		ball->setPosY(ball->getPosY());


	}
	if (checkCollicionwithpowerup()) {

		ball->setCollisionWithpowerup(true);
		delete powerup;
		powerup = nullptr;


	}

	if (player->getScore() >= 10 || player2->getScore() >= 10) {
		status = STATUS_ENDING;
	}
}

void Game::updateEndingScreen() {
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		graphics::destroyWindow();
		exit(0);
	}



}

//Draw the start Screen of game
void Game::drawStartScreen()
{

	graphics::Brush br;
	char info1[40];
	char info2[40];
	char info3[40];
	char info4[40];
	char info5[80];
	char info6[40];
	char info7[40];
	sprintf_s(info6, "Player1 buttons (W S)");
	sprintf_s(info7, "Player2 buttons (UP DOWN)");
	sprintf_s(info1, "Press 1 For EASY");
	sprintf_s(info2, "Press 2 For MEDIUM");
	sprintf_s(info3, "Press 3 For HARD");
	sprintf_s(info4, "AND PRESS ENTER TO CONTINUE");
	sprintf_s(info5, "Extra: powerup gives a point if it's hit to a random player");
	graphics::drawText((CANVAS_WIDTH / 2) - 160, (CANVAS_HEIGHT / 2)-40,		 30, info1, br);
	graphics::drawText((CANVAS_WIDTH / 2) - 160, (CANVAS_HEIGHT / 2)-5, 30, info2, br);
	graphics::drawText((CANVAS_WIDTH / 2) - 160, (CANVAS_HEIGHT / 2)+30, 30, info3, br);
	graphics::drawText((CANVAS_WIDTH / 2) - 240, (CANVAS_HEIGHT / 2) + 120, 30, info4, br);
	graphics::drawText((CANVAS_WIDTH / 2)-130 , CANVAS_HEIGHT -20, 22, info5, br);
	graphics::drawText(35, 30, 20, info6, br);
	graphics::drawText(35, 60, 20, info7, br);



	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		easy = true;
		usererror = true;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		medium = true;
		usererror = true;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		hard= true;
		usererror = true;
	}
}

void Game::drawLevelScreen()
{
	//draw backgournd 
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	if (ball && ball->getRally() >= 10) {
		br.texture = std::string(ASSET_PATH) + "background2.png";
	}


	
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	//draw player
	if (player)
		player->draw();

	if (player2)
		player2->draw();

	if (ball)
		ball->draw();
	if (powerup)
		powerup->draw();
	//UI.indo layer

	if (player && debug_mode) {
		char info[40];
		sprintf_s(info, "Player pos: (%5.1f, %5.1f)", player->getPosX(), player->getPosY());
		graphics::drawText(20, 20, 15, info, br);
	}


	if (ball &&ball->getRally() >= 1) {
		char info[20];
		sprintf_s(info, "Rally:%d", ball->getRally());
		graphics::drawText(CANVAS_WIDTH - 150, 20, 25, info, br);

	}
	if (player) {
		char info[40];
		sprintf_s(info, "Player1: \t %d  | \t Player2: \t %d", player->getScore(), player2->getScore());
		graphics::drawText((CANVAS_WIDTH / 2) - 150, 20, 25, info, br);
	}
}


void Game::drawEndingScreen() {

	graphics::Brush br;
	char info[40];
	char info2[40];
	if (player->getScore() >= 10) {
		sprintf_s(info, "Player1 winner");
		graphics::drawText(170, (CANVAS_HEIGHT / 2), 100, info, br);
	}else {

		sprintf_s(info, "Player2 winner");
		graphics::drawText(170, (CANVAS_HEIGHT / 2), 100, info, br);	
	}

	sprintf_s(info, "PRESS ENTER TO FINISH");
	graphics::drawText((CANVAS_WIDTH / 2)-160, (CANVAS_HEIGHT / 2)+80, 30, info, br);


}
//check if ball hit player
bool Game::checkCollicion()
{

	if (!player || !ball)
	{
		return false;
	}

	Rect d1 = player->getCollisionHull();
	Rect d3 = player2->getCollisionHull();
	Rect d2 = ball->getCollisionHull();


	
	d1.cy = d1.cy - (player->getHeight()/2);
	d3.cy = d3.cy - (player2->getHeight() / 2);

	//check collision between two rectangles(player and ball)
	if (d1.cx < d2.cx + d2.width && d1.cx + d1.width > d2.cx && d1.cy < d2.cy + d2.height && d1.cy + d1.height > d2.cy) {
		return true;
	
	}
	else if(d3.cx < d2.cx + d2.width && d3.cx + d3.width > d2.cx && d3.cy < d2.cy + d2.height && d3.cy + d3.height > d2.cy) {
		return true;
	}
	else {
		return false;
	}


}

bool Game::checkCollicionwithpowerup() {
if (!ball || !powerup)
{
	return false;
}

Rect d4 = powerup->getCollisionHull();
Rect d2 = ball->getCollisionHull();

float dx4 = d2.cx - d4.cx;
float dy4 =d2.cx - d4.cx;

//check collision between two rectangles(powerup and ball)
if (d4.cx < d2.cx + d2.width && d4.cx + d4.width > d2.cx && d4.cy < d2.cy + d2.height && d4.cy + d4.height > d2.cy)
{
	return true;
}
else
	 return false;
}




//Set for eatch player buttons from the keyboard
 void Game::updateKeys() {
	
	float pos_x = player->getPosX();
	float pos_y = player->getPosY();
	float speed = player->getSpeed();

	float pos_x2 = player2->getPosX();
	float pos_y2 = player2->getPosY();
	float speed2 = player2->getSpeed();


	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		pos_y2 -= speed2 * graphics::getDeltaTime() / 10.0f;
		player2->setPosX(pos_y2);
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		pos_y2 += speed2 * graphics::getDeltaTime() / 10.0f;
		player2->setPosX(pos_y2);
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		player->setPosX(pos_y);
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
		player->setPosX(pos_y);
	}

	//check if players go out of bounds
	if (player->getPosY() > CANVAS_HEIGHT) player->setPosX(CANVAS_HEIGHT);
	if (player->getPosY() < 0) player->setPosX(0.0f);

	if (player2->getPosY() < 0) player2->setPosX(0.0f);
	if (player2->getPosY() > CANVAS_HEIGHT) player2->setPosX(CANVAS_HEIGHT);	
}


 //create new powerup
 void Game::spawnPowerup()
 {
	 if (!powerup && ball && ball->getRally() >= 10 && ball->getRally()<=15)
	 {
		 powerup = new PowerUp(*this);
		 
	 }
 }


 //if ball dont's exist create new
void Game::spawnball()
{
	if (!ball)
	{
		ball = new Enemy(*this);

	}
}


//if ball go out of bounds delete and give point to player
void Game::chechball()
{
	if (ball && !ball->isActive())
	{
		if (ball->isGoalA()) {

			player->setScore();
			graphics::playMusic(std::string(ASSET_PATH) + "score.mp3", 1.0f, false, 0);
			ball->setRally(0);
			ball->setGoalA(false);
		}
		if (ball->isGoalB()) {

			player2->setScore();
			graphics::playMusic(std::string(ASSET_PATH) + "score.mp3", 1.0f, false, 0);
			ball->setRally(0);
			ball->setGoalB(false);

		}
		delete ball;
		ball = nullptr;

	}
}


float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}
float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_width;
}

Game::Game()
{
}

Game::~Game()
{
}
