#pragma once

#include "EntityController.h"

class PlayerController : public EntityController
{
public:
	using super = EntityController;
	PlayerController(Entity* entity);

	virtual void Update(float deltaTime) override;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	Entity* entity;
};