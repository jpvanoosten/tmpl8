#pragma once

class Entity;

/// <summary>
/// A controller is an interface type attached to an Entity (like a player or Enemy entity).
/// </summary>
class EntityController
{
public:
	// The minimum requirement of any interface is a virtual destructor.
	virtual ~EntityController() = default;

	/// <summary>
	/// Update the entity controller.
	/// </summary>
	/// <param name="deltaTime">The time between frames (in seconds).</param>
	virtual void Update(float deltaTime) = 0;

protected:

private:
};