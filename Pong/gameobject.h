#pragma once

#include "util.h"

class Collidable
{
public:
	virtual Rect getCollisionHull()  = 0;


};

class GameObject
{
protected:
	const class Game & game;

public:
	GameObject(const class Game& mygame);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};