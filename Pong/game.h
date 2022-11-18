#pragma once

#include "player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "config.h"


class Game
{
	typedef enum { STATUS_START, STATUS_PLAYING,STATUS_ENDING } status_t;
	status_t status = STATUS_START;
	
	Player* player = nullptr;
	Player* player2 = nullptr;
	Enemy* ball = nullptr;
	PowerUp* powerup = nullptr;
	
	bool player_initiallized = false;
	bool debug_mode = false;
	
	unsigned int window_width = WINDOW_WIDTH,
				window_height = WINDOW_HEIGHT;
	bool end=false;
	
public:
	void update();
	void draw();
	void init();

	void spawnball();
	void chechball();
	void spawnPowerup();

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndingScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndingScreen();
	bool checkCollicion();
	bool checkCollicionwithpowerup();

	void updateKeys();
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimesions(unsigned int w, unsigned int h) {
		window_width = w; window_height = h;
	}

	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	
	Game();
	~Game();

};

