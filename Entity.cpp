#include "Entity.h"
#include "Component.h"

Entity::~Entity()
{
	for (auto c : components)
	{
		delete c;
	}
}

void Entity::AddComponent(Component* component)
{
	components.push_back(component);
}

void Entity::Update()
{
	for (auto c : components)
	{
		c->Update();
	}
}

void Entity::Render(Tmpl8::Surface& screen)
{
	for (auto c : components)
	{
		c->Render(screen);
	}

}

void Entity::KeyDown(SDL_Scancode key)
{
	for (auto c : components)
	{
		c->KeyDown(key);
	}

}

void Entity::KeyUp(SDL_Scancode key)
{
	for (auto c : components)
	{
		c->KeyUp(key);
	}
}

void Entity::MouseMove(int x, int y)
{
	for (auto c : components)
	{
		c->MouseMove(x, y);
	}
}

void Entity::MouseDown(int button)
{
	for (auto c : components)
	{
		c->MouseDown(button);
	}
}

void Entity::MouseUp(int button)
{
	for (auto c : components)
	{
		c->MouseUp(button);
	}
}
