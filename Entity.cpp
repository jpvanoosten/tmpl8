#include "Entity.h"
#include "EntityController.h"

Entity::Entity(Tmpl8::Surface* spriteTexture, int numFrames, const Bounds& bounds, const Tmpl8::vec2& position, const Tmpl8::vec2& anchor)
	: sprite(spriteTexture, numFrames)
	, bounds(bounds)
	, position(position)
	, anchor(anchor)
{}

void Entity::Draw(Tmpl8::Surface& screen)
{
	int x = position.x - anchor.x * sprite.GetWidth();
	int y = position.y - anchor.y * sprite.GetHeight();

	sprite.Draw(&screen, x, y);
}
