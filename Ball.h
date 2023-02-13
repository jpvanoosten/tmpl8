#pragma once

#include "Circle.h"
#include "surface.h"


class Ball
{
public:
    Ball();

    explicit Ball(const Circle& circle, const Tmpl8::vec2& velocity);

    void Update(float deltaTime);

    void Draw(Tmpl8::Surface& screen);

    const Circle& getCircle() const;

    void setPosition(const Tmpl8::vec2& pos);
    void setRadius(float radius);

    const Tmpl8::vec2& getVelocity() const;
    void setVelocity(const Tmpl8::vec2& vel);

private:
    Circle circle;
    Tmpl8::vec2 velocity{0};
    Tmpl8::Sprite sprite;
};

