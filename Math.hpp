#pragma once

// Source: https://grok.com (March 8th, 2025). "What is the best way to implement a character controller for a 2D platforming game?"
constexpr float sign(float v)
{
    return v > 0.0f ? 1.0f : v < 0.0f ? -1.0f : 0.0f;
}

// std::abs but constexpr
constexpr float absolute(float v)
{
    return v < 0.0f ? -v : v;
}

// Source: https://grok.com (March 8th, 2025). "What is the best way to implement a character controller for a 2D platforming game?"
// Move the current value towards teh target value with a maximum delta.
constexpr float moveToward(float current, float target, float maxDelta)
{
    // Calculate the difference between current and target.
    float diff = target - current;

    // If the difference is smaller than maxDelta, just return the target.
    if (absolute(diff) < maxDelta)
        return target;

    // Otherwise, move by maxDelta in the direction of the target.
    return current + sign(diff) * maxDelta;
}

// Source: https://grok.com (March 17th, 2025) "I want to implement a 2D camera for my platforming game. I want to include variables like x, and y damping and look-ahead."
// Smooth damping function.
constexpr float smoothDamp( float current, float target, float damping, float deltaTime)
{
    float speed = damping * deltaTime;
    return moveToward(current, target, speed * absolute(target - current));
}