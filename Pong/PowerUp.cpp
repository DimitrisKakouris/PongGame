#include "powerup.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "game.h"
#include <iostream>




void PowerUp::update() {


	

}

void PowerUp::draw() {

	brush.texture = std::string(ASSET_PATH) + "ball.png";
	brush.fill_opacity = 1.0f;
	Rect hull = getCollisionHull();
	graphics::drawRect(hull.cx, hull.cy, hull.height, hull.width, brush);
	graphics::resetPose();

	if (game.getDebugMode()) {

		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		
		graphics::drawRect(hull.cx, hull.cy, hull.height, hull.width, br);
	}

}

void PowerUp::init() {

	pos_x = randomHeight();
	pos_y = randomWidth();
	size = 20;
	brush.outline_opacity = 0.0f;
}

PowerUp::PowerUp(const Game& mygame)
	:GameObject(mygame) {
	init();
}

PowerUp::~PowerUp() {

}

Rect PowerUp::getCollisionHull()  {
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.height = 40;
	rect.width = 40;
	return rect;
}
