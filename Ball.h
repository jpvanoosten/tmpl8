#pragma once
#include "surface.h"
#include "template.h"

class Ball
{
public:
    Ball(const tmpl8::vec2& pos = tmpl8::vec2(0.0f), const tmpl8::vec2& vel = tmpl8::vec2(0.0, 0.0f));
    ~Ball();

    // Simulate a single step of the ball.
    void Update(float deltaTime);

    void Draw(tmpl8::Surface* target) const;

    void SetPos(const tmpl8::vec2& pos);
    const tmpl8::vec2& GetPos() const;
    tmpl8::vec2& GetPos();

    void SetVelocity(const tmpl8::vec2& vel);
    const tmpl8::vec2& GetVelocity() const;
    tmpl8::vec2& GetVelocity();

    void SetMass(float mass);
    float GetMass() const;

    // Get the width of the ball sprite (in pixels).
    float GetWidth() const;
    // Get the height of the ball sprite (in pixels).
    float GetHeight() const;

    // Get the top of the sprite (in pixels).
    float GetTop() const;
    void SetTop(float top);

    // Get the bottom of the sprite (in pixels).
    float GetBottom() const;
    void SetBottom(float bottom);

    // Get the left of the sprite (in pixels).
    float GetLeft() const;
    void SetLeft(float left);

    // Get the right of the sprite (in pixels).
    float GetRight() const;
    void SetRight(float right);

    // Get the size of the collision radius of the ball.
    float GetRadius() const;

    // Check to see if this ball collides with another ball.
    bool Collides(const Ball& ball);

private:
    // The sprite used to draw all of the balls.
    // It's static because the same sprite is used 
    // to draw all of the balls, so there should be only 1.
    static tmpl8::Sprite ms_Sprite;

    // The 2D position of the ball on the screen.
    // This is the center point of the ball.
    // When rendering, it is drawn from the top-left 
    // corner of the sprite.
    tmpl8::vec2 pos;

    // The current velocity of the ball (in m/s).
    tmpl8::vec2 vel;

    // The mass of the ball (in kg).
    float mass = 1.0f;

    // The radius of the ball (in pixels).
    float radius = 25.0f;
};

