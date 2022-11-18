#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"
#include "util.h"


class PowerUp : public GameObject, public Collidable {

	graphics::Brush brush;

	float pos_y;
	float pos_x;
	float size;
	bool active = true;//check if out of bounds


public:
	void update() override;
	void draw() override;
	void init() override;

	//setters
	void setPosX(float pos_x) { this->pos_x = pos_x; }
	void setPosY(float pos_y) { this->pos_y = pos_y; }

	//Getters
	bool isActive() { return active; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	float getSize() { return size; }


	PowerUp(const class Game& mygame);
	~PowerUp();
	Rect getCollisionHull()  override;





};