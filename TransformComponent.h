#pragma once

#include "template.h"
#include "Component.h"

class TransformComponent : public Component
{
public:
	TransformComponent() = default;

	virtual void Update() override;

	virtual void Render(Tmpl8::Surface& screen) override;

	void SetPosition(const Tmpl8::vec2& position)
	{
		this->position = position;
	}

	const Tmpl8::vec2& GetPosition() const
	{
		return position;
	}

private:
	Tmpl8::vec2 position;
};

