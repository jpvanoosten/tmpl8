#pragma once

#include <SDL_scancode.h>
//#include <vector>
#include <unordered_map>
#include <typeindex>

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

	/// <summary>
	/// Entities store a list of pointers to components that they take ownership of.
	/// Making copies would result in multiple entities taking ownership of the same
	/// component, and would result in the component being deleted for each copy of 
	/// the entity.
	/// </summary>
	/// <remarks>An entity can be moved, but it cannot be copied.</remarks>
	/// <param name="copy"></param>
	Entity(const Entity& copy) = delete;

	/// <summary>
	/// Move contrstructor.
	/// </summary>
	/// <param name="copy"></param>
	/// <returns></returns>
	Entity(Entity&& copy) noexcept = default;

	~Entity();

	/// <summary>
	/// Add a component to this entity.
	/// </summary>
	/// <param name="component"></param>
	template<typename T, typename... Args>
	void AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent() const;

	template<typename T>
	std::vector<T*> GetComponents() const;

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
	std::unordered_multimap<std::type_index, Component*> components;
};

template<typename T, typename... Args>
void Entity::AddComponent(Args&&... args)
{
	components.insert({ typeid(T), new T(std::forward(args)...) });
}

template<typename T>
T* Entity::GetComponent() const
{
	auto iter = components.find(typeid(T));
	if (iter != components.end())
	{
		return dynamic_cast<T*>((*iter).second);
	}

	return nullptr;
}

template<typename T>
std::vector<T*> Entity::GetComponents() const
{
	auto range = components.equal_range(typeid(T));
	std::vector<T*> res;

	for (auto it = range.first; it != range.second; ++it) {
		res.push_back(dynamic_cast<T*>(it->second));
	}
	
	return res;
}
