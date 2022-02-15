#pragma once

#include <SDL_scancode.h>

namespace Tmpl8
{
	class Surface;
}

class Component
{
public:
	/// <summary>
	/// Update the component.
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update();

	/// <summary>
	/// Render the component.
	/// </summary>
	virtual void Render(Tmpl8::Surface& screen);

	/// <summary>
	/// A key was pressed.
	/// </summary>
	/// <param name="key"></param>
	virtual void KeyDown(SDL_Scancode key);

	/// <summary>
	/// A key was released.
	/// </summary>
	/// <param name="key"></param>
	virtual void KeyUp(SDL_Scancode key);

	/// <summary>
	/// The mouse was moved.
	/// </summary>
	/// <param name="x">Screen space.</param>
	/// <param name="y"></param>
	virtual void MouseMove(int x, int y);

	/// <summary>
	/// A button on the mouse was pressed.
	/// </summary>
	/// <param name="button"></param>
	virtual void MouseDown(int button);

	virtual void MouseUp(int button);


protected:
	/// <summary>
	/// Do not construct directly!.
	/// </summary>
	Component() = default;

private:
};