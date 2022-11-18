#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "game.h"
#include <iostream>
#include "difficulty.h"




void Enemy::update() {

	pos_x = pos_x  + speed * graphics::getDeltaTime();
	pos_y = pos_y + speedball * graphics::getDeltaTime();


	//Check if ball hit player
	if (collisionWithPlayer && pos_x>=(CANVAS_WIDTH/2)-1) { //collision left
		speed = -1*standartSpeedo;
		collisionWithPlayer = false;
		rally++;
		graphics::playSound(std::string(ASSET_PATH) + "playerpong.mp3", 1.0f, false);

	}
	if (collisionWithPlayer && pos_x < (CANVAS_WIDTH / 2) + 1) {//collision right
		speed = standartSpeedo;
		collisionWithPlayer = false;
		rally++;
		graphics::playSound(std::string(ASSET_PATH) + "playerpong.mp3", 1.0f, false);

	}
	//check if ball hit powerup
	if (Collicionwithpowerup && pos_x >= (CANVAS_WIDTH / 2) - 1) {//collision left
		goalA = true;
		active = false;//out of bounds delete 
	}

	if (Collicionwithpowerup && pos_x < (CANVAS_WIDTH / 2) + 1) {//collision right
		goalB = true;
		active = false;//out of bounds delete 
	}
	
	//Check when ball going out of canvas
	if (pos_x < -size) {
		active = false;//out of bounds delete 
		goalB = true;

	}	
	if (pos_x > CANVAS_WIDTH) {
		active = false;//out of bounds delete 
		goalA = true;
	}
	if (pos_y < 5) {//top
		speedball = standartSpeedo;
		graphics::playSound(std::string(ASSET_PATH) + "wallhit.mp3", 1.0f, false);
	}
	if (pos_y > CANVAS_HEIGHT -size) {//bottom
		speedball = -1*standartSpeedo;
		graphics::playSound(std::string(ASSET_PATH) + "wallhit.mp3", 1.0f, false);
	}

}

void Enemy::draw() {
	
	brush.texture = std::string(ASSET_PATH) + "ball.png";
	brush.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();


	//active only when debug mode is true in main
	if (game.getDebugMode()) { 

		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Rect hull = getCollisionHull();
		graphics::drawRect(hull.cx, hull.cy, hull.height, hull.width, br);
	}

}

void Enemy::init() {
	speed = standartSpeedo *randoPlin1to1();
	speedball = standartSpeedo * randoPlin1to1();
	pos_x = (CANVAS_WIDTH / 2) + 1.1f * size;
	pos_y = randomHeightforball();
	size = 20 ;
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game & mygame)
	:GameObject(mygame) {
	init();
}

Enemy::~Enemy() {

}

Rect Enemy::getCollisionHull()  {
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.height = 20;
	rect.width = 20;
	return rect;
}
