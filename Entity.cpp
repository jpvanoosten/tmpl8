#include "Entity.h"
#include "Component.h"

#include <utility>

Entity::~Entity()
{
	for (auto& iter : components)
	{
		delete iter.second;
	}
}

void Entity::Update()
{
	for (auto& iter : components)
	{
		iter.second->Update(*this);
	}
}

void Entity::Render(Tmpl8::Surface& screen)
{
	for (auto& iter : components)
	{
		iter.second->Render(*this, screen);
	}

}

void Entity::KeyDown(SDL_Scancode key)
{
	for (auto& iter : components)
	{
		iter.second->KeyDown(*this, key);
	}

}

void Entity::KeyUp(SDL_Scancode key)
{
	for (auto& iter : components)
	{
		iter.second->KeyUp(*this, key);
	}
}

void Entity::MouseMove(int x, int y)
{
	for (auto& iter : components)
	{
		iter.second->MouseMove(*this, x, y);
	}
}

void Entity::MouseDown(int button)
{
	for (auto& iter : components)
	{
		iter.second->MouseDown(*this, button);
	}
}

void Entity::MouseUp(int button)
{
	for (auto& iter : components)
	{
		iter.second->MouseUp(*this, button);
	}
}
