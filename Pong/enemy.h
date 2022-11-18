#pragma once

#include "gameobject.h"
#include "graphics.h"
#include "config.h"
#include "util.h"


class Enemy : public GameObject,public Collidable {

	graphics::Brush brush;
	
	float pos_y;
	float pos_x;
	float speed;
	float size;
	float speedball;
	int rally=0;
	float height;
	float width;
	
	bool active = true;//check if out of bounds
	bool goalA = false;//check if player1 take point
	bool goalB = false;	
	bool collisionWithPlayer = false;

	bool Collicionwithpowerup = false;
	
public:
	void update() override;
	void draw() override;
	void init() override;

	//setters
	void setPosX(float pos_x) { this->pos_x = pos_x; }
	void setPosY(float pos_y) { this->pos_y = pos_y; }
	void setGoalA(bool goalA) { this->goalA = goalA; }
	void setGoalB(bool goalB) { this->goalB = goalB; }
	void setRally(int rally) { this->rally = rally; }
	void setSpeed(float speed) { this->speed = speed; }
	void ChangesDirection() { this->speed = -1 * speed; }
	void setCollisionWithPlayer(bool collisionWithPlayer) { this->collisionWithPlayer = collisionWithPlayer; }
	void setCollisionWithpowerup(bool Collicionwithpowerup) { this->Collicionwithpowerup = Collicionwithpowerup; }
	//Getters
	bool isActive() { return active; }
	bool isGoalA() { return goalA; }
	bool isGoalB() { return goalB; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	int getRally() { return rally; }
	float getSize() { return size; }
	float getSpeed() { return speed; }
	float getHeight() { return height; }
	float getWidth() { return width; }
	

	Enemy(const class Game & mygame);
	~Enemy();
	Rect getCollisionHull()  override;


	


};