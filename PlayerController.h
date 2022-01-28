#pragma once

#include "EntityController.h"
#include "TileMap.h"

class PlayerController : public EntityController
{
public:
	using super = EntityController;
	PlayerController(Entity* player, TileMap* tileMap);

	virtual void Update(float deltaTime) override;

	void MoveLeft(bool left);
	void MoveRight(bool right);
	void MoveUp(bool up);
	void MoveDown(bool down);

private:
	Entity* player;
	TileMap* tileMap;
	// Speed the player can move (in pixels per second).
	float speed = 50.0f;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
};