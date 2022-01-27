#pragma once

#include "template.h"
#include "surface.h"
#include "EntityController.h"

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
	/// <param name="controller">The EntityController (could be a player, or an enemy controller)</param>
	Entity(Tmpl8::Surface* spriteTexture, int numFrames, EntityController* controller);

	/// <summary>
	/// Update the Entity.
	/// </summary>
	/// <param name="deltaTime">The elapsed time this frame (in seconds).</param>
	virtual void Update(float deltaTime);

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
	/// position of the entity relative to the position of the sprite.
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
	/// Set the frame of the animation in the sprite.
	/// </summary>
	/// <param name="frame">The </param>
	void SetFrame(int frame)
	{
		this->frame = frame;
	}

	/// <summary>
	/// Get the current frame of the animation in the sprite.
	/// </summary>
	/// <returns>The current frame of the sprite animation.</returns>
	int GetFrame() const
	{
		return frame;
	}


protected:

private:
	EntityController* controller = nullptr;
	Tmpl8::Sprite sprite;
	Tmpl8::vec2 position;
	Tmpl8::vec2 anchor;
	int frame = 0;
};