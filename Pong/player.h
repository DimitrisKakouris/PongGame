#pragma once
#include "gameobject.h"
#include "config.h"
#include "graphics.h"

class Player : public GameObject, public Collidable
{
	float speed = 2.0f;
	int width;
	int heightpl;
	float pos_x;
	float pos_y;

	int score = 0;

public:
	Player(const class Game & mygame);

	void update() override;
	void draw() override;
	void init() override;
	
	void setScore() { this->score = score + 1;}
	void setPosY(float pos_x) { this->pos_x = pos_x; }
	void setPosX(float pos_y) { this->pos_y = pos_y; }
	void setWidth(int width) { this->width = width; }
	void setHeight(int heightpl) { this->heightpl = heightpl; }

	float getPosY() { return pos_y; }
	float getSpeed() { return speed; }
	float getPosX() { return pos_x; }
	int getScore() { return score; }
	int getHeight() { return heightpl; }
	int getWidth() { return width; }
	Rect getCollisionHull()  override;

	
};
