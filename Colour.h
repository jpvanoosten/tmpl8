#pragma once

#include <algorithm>
#include <cstdint>

struct Colour
{
	union
	{
		uint32_t i;
		struct
		{
			uint8_t a, r, g, b;
		};
	};

	explicit Colour(uint32_t c)
		: i(c)
	{}

	Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{}

	Colour operator+(const Colour& rhs) const
	{
		return {
			static_cast<uint8_t>(std::max(r + rhs.r, 255)),
			static_cast<uint8_t>(std::max(g + rhs.g, 255)),
			static_cast<uint8_t>(std::max(b + rhs.b, 255)),
			static_cast<uint8_t>(std::max(a + rhs.a, 255))
		};
	}

};

Colour operator*(const Colour& lhs, float rhs)
{
	float r = lhs.r / 255.0f;
	float g = lhs.g / 255.0f;
	float b = lhs.b / 255.0f;
	float a = lhs.a / 255.0f;

	return {
		static_cast<uint8_t>(std::max(r * rhs, 1.0f) * 255),
		static_cast<uint8_t>(std::max(g * rhs, 1.0f) * 255),
		static_cast<uint8_t>(std::max(b * rhs, 1.0f) * 255),
		static_cast<uint8_t>(std::max(a * rhs, 1.0f) * 255),
	};
}

Colour operator*(float lhs, const Colour& rhs)
{
	return rhs * lhs;
}
