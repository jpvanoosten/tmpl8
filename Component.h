#pragma once

#include <SDL_scancode.h>
#include <string>

namespace Tmpl8
{
	class Surface;
}

class Entity;

class Component
{
public:
	static const std::string& ID()
	{
		static std::string id = "Component";
		return id;
	}

	virtual const std::string& GetID()
	{
		return ID();
	}

	/// <summary>
	/// Update the component.
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(Entity& entity);

	/// <summary>
	/// Render the component.
	/// </summary>
	virtual void Render(Entity& entity, Tmpl8::Surface& screen);

	/// <summary>
	/// A key was pressed.
	/// </summary>
	/// <param name="key"></param>
	virtual void KeyDown(Entity& entity, SDL_Scancode key);

	/// <summary>
	/// A key was released.
	/// </summary>
	/// <param name="key"></param>
	virtual void KeyUp(Entity& entity, SDL_Scancode key);

	/// <summary>
	/// The mouse was moved.
	/// </summary>
	/// <param name="x">Screen space.</param>
	/// <param name="y"></param>
	virtual void MouseMove(Entity& entity, int x, int y);

	/// <summary>
	/// A button on the mouse was pressed.
	/// </summary>
	/// <param name="button"></param>
	virtual void MouseDown(Entity& entity, int button);

	/// <summary>
	/// A button on the mouse was released.
	/// </summary>
	/// <param name="button"></param>
	virtual void MouseUp(Entity& entity, int button);

protected:
	/// <summary>
	/// Do not construct directly!.
	/// </summary>
	Component() = default;

private:
};