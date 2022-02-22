#pragma once
#include "Component.h"

class ColliderComponent : public Component
{
public:
	/// <summary>
	/// Update the component.
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(Entity& entity);

};

