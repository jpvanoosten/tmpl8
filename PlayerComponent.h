#pragma once
#include "Component.h"

class PlayerComponent : public Component
{
public:

	static const std::string& ID()
	{
		static std::string id = "PlayerComponent";
		return id;
	}

	virtual const std::string& GetID()
	{
		return ID();
	}



protected:

private:

};

