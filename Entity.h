#pragma once

#include "Bounds.h"
#include "surface.h"
#include "template.h"

class EntityController;

/// <summary>
/// An Entity is an object that can appear in the game (like the player entity or an enemy character).
/// </summary>
class Entity
{
public:
	/// <summary>
	/// Create a new entity.
	/// </summary>
	/// <param name="spriteTexture">The surface that contains the sprite texture for this entity.</param>
	/// <param name="numFrames">The number of frames in the sprite texture.</param>
	/// <param name="bounds">The bouding box of the entity relative to the entity's position.</param>
	/// <param name="position">The initial position of the entity.</param>
	/// <param name="anchor">The normalized anchor position of the sprite.</param>
	Entity(Tmpl8::Surface* spriteTexture, int numFrames, const Bounds& bounds, const Tmpl8::vec2& position = Tmpl8::vec2(0.0f), const Tmpl8::vec2& anchor = Tmpl8::vec2(0.5f));

	/// <summary>
	/// Draw this entity to the screen.
	/// </summary>
	/// <param name="screen">The surface to draw this entity to.</param>
	virtual void Draw(Tmpl8::Surface& screen);

	/// <summary>
	/// Set the screen-space position of the entity.
	/// </summary>
	/// <param name="position">The screen-space position to set this entity to.</param>
	void SetPosition(const Tmpl8::vec2 position)
	{
		this->position = position;
	}

	/// <summary>
	/// Get the screen-space position of the entity.
	/// </summary>
	/// <returns>The screen-space position of the entity.</returns>
	const Tmpl8::vec2& GetPosition() const
	{
		return position;
	}

	/// <summary>
	/// The (normalized) anchor-point of the sprite determines the
	/// position of the sprite relative to the position of the entity.
	/// An anchor-point of (0, 0) makes the entity's position the top-left
	/// corner of the sprite. An anchor-point of (0.5, 0.5) makes the entity's
	/// position the center of the sprite, and an anchor point of (1, 1) makes
	/// the entity's position the bottom-right corner of the sprite.
	/// </summary>
	/// <param name="anchor">The normalized anchor-point of the sprite.</param>
	void SetAnchor(const Tmpl8::vec2& anchor)
	{
		this->anchor = anchor;
	}

	/// <summary>
	/// Get the anchor-point of the sprite.
	/// </summary>
	/// <returns></returns>
	const Tmpl8::vec2 GetAnchor() const
	{
		return anchor;
	}

	/// <summary>
	/// Get the bounds of the entity in screen space.
	/// </summary>
	/// <returns>The screen space bounds of the entity.</returns>
	Bounds GetBounds() const
	{
		return bounds.At(position);
	}

	/// <summary>
	/// Set the frame of the animation in the sprite.
	/// </summary>
	/// <param name="frame">The animation frame.</param>
	void SetFrame(int frame)
	{
		sprite.SetFrame(frame);
	}

	/// <summary>
	/// Get the current frame of the animation in the sprite.
	/// </summary>
	/// <returns>The current frame of the sprite animation.</returns>
	int GetFrame() const
	{
		return sprite.GetFrame();
	}

protected:

private:
	Tmpl8::Sprite sprite;
	Bounds bounds;
	Tmpl8::vec2 position;
	Tmpl8::vec2 anchor;
};