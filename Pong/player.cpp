#include "player.h"
#include "graphics.h"
#include "game.h"
#include<iostream>


Player::Player(const Game & mygame)
	: GameObject(mygame)
{

}

void Player::update()
{
	

}


void Player::draw() {

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "player2.png";
	Rect hull = getCollisionHull();
	graphics::drawRect(hull.cx, hull.cy,  hull.width, hull.height, br);
	graphics::resetPose();


	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		graphics::drawRect(hull.cx, hull.cy, hull.width,hull.height,  br);
	}

}

void Player::init()
{

}

Rect Player::getCollisionHull() 
{
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.height = getHeight();
	rect.width = getWidth();
	return rect;
}


