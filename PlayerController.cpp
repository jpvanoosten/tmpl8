#include "template.h"
#include "Entity.h"
#include "PlayerController.h"
#include "TileMap.h"

using namespace Tmpl8;

PlayerController::PlayerController(Entity* player, TileMap* tileMap)
	: player(player)
	, tileMap(tileMap)
{}

void PlayerController::Update(float deltaTime)
{
	vec2 p = player->GetPosition();
	vec2 d{ 0 };
	Bounds playerBounds = player->GetBounds();

	if (moveLeft)
	{
		d.x -= speed * deltaTime;
	}
	if (moveRight)
	{
		d.x += speed * deltaTime;
	}
	if (moveUp)
	{
		d.y -= speed * deltaTime;
	}
	if (moveDown)
	{
		d.y += speed * deltaTime;
	}

	if (!tileMap->Collides(playerBounds.At({ d.x, 0 })))
	{
		tileMap->Translate({ -d.x, 0 });
	}
	if (!tileMap->Collides(playerBounds.At({ 0, d.y })))
	{
		tileMap->Translate({ 0, -d.y });
	}
}

void PlayerController::MoveLeft(bool left)
{
	moveLeft = left;
}

void PlayerController::MoveRight(bool right)
{
	moveRight = right;
}

void PlayerController::MoveUp(bool up)
{
	moveUp = up;
}

void PlayerController::MoveDown(bool down)
{
	moveDown = down;
}
