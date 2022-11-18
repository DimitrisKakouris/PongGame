#include "player.h"
#include "graphics.h"
#include "game.h"


Player::Player(const Game& mygame)
	: GameObject(mygame)
{

}

void Player::update()
{

	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}


	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_WIDTH) pos_y = CANVAS_WIDTH;

}


void Player::draw() {

	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	graphics::setOrientation(-90.f);
	graphics::setScale(height, height);
	br.fill_opacity = 0.5f;
	br.texture = std::string(ASSET_PATH) + "boy1.png";
	graphics::drawRect(pos_x - 10 * height, pos_y + 30 * 3 * height, 100, 100, br);

	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "boy2.png";
	graphics::drawRect(pos_x, pos_y, 100, 100, br);

	graphics::resetPose();

	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(height, height);
	graphics::drawDisk(pos_x - 50 * height, pos_y, 20, br);
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

		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}

}

void Player::init()
{

}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}

