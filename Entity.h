#pragma once

#include <SDL_scancode.h>
#include <vector>

class Component;

namespace Tmpl8
{
	class Surface;
}

/// <summary>
/// An Entity is an object that can appear in the game (like the player entity or an enemy character).
/// </summary>
class Entity
{
public:
	/// <summary>
	/// Create a new entity.
	/// </summary>
	Entity() = default;

	Entity(const Entity& copy) = default;
	Entity(Entity&& copy) noexcept;
	
	~Entity();

	/// <summary>
	/// Add a component to this entity.
	/// </summary>
	/// <param name="component"></param>
	void AddComponent(Component* component);

	/// <summary>
	/// Update the entity.
	/// </summary>
	/// <param name="deltaTime">Elapsed time in seconds.</param>
	void Update();

	/// <summary>
	/// Draw this entity to the screen.
	/// </summary>
	/// <param name="screen">The surface to draw this entity to.</param>
	void Render(Tmpl8::Surface& screen);

	void KeyDown(SDL_Scancode key);

	void KeyUp(SDL_Scancode key);

	void MouseMove(int x, int y);

	void MouseDown(int button);

	void MouseUp(int button);

protected:

private:
	std::vector<Component*> components;
};