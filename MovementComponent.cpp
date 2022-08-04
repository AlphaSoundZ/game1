#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
    float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), 
    maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

// Functions
void MovementComponent::update(const float& dt)
{
    // Deceleration
    if (this->velocity.x > 0.f)
    {
        // Deceleration x positive
        this->velocity.x -= deceleration*dt;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0;
    }
    else if (this->velocity.x < 0.f)
    {
        // Deceleration x negative
        this->velocity.x += deceleration*dt;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0;
    }
    if (this->velocity.y > 0.f)
    {
        // Deceleration y positive
        this->velocity.y -= deceleration*dt;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0;
    }
    else if (this->velocity.y < 0.f)
    {
        // Deceleration y negative
        this->velocity.y += deceleration*dt;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0;
    }
    // Max velocity check
    if (this->velocity.y > this->maxVelocity*dt)
        this->velocity.y = this->maxVelocity*dt;
    if (this->velocity.y < -this->maxVelocity*dt)
        this->velocity.y = -this->maxVelocity*dt;
    if (this->velocity.x > this->maxVelocity*dt)
        this->velocity.x = this->maxVelocity*dt;
    if (this->velocity.x < -this->maxVelocity*dt)
        this->velocity.x = -this->maxVelocity*dt;

    // Final move
    this->sprite.move(this->velocity); // Uses velocity
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x * dt;
    this->velocity.y += this->acceleration * dir_y * dt;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}

const float MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state)
{
    bool result = false;
    switch (state)
    {
    case IDLE:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f)
            result = true;
        break;
    case IDLE_DOWN:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f && (this->lastState == MOVING_DOWN || this->lastState == IDLE_DOWN))
            result = true;
        break;
    case IDLE_UP:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f && (this->lastState == MOVING_UP || this->lastState == IDLE_UP))
            result = true;
        break;
    case IDLE_LEFT:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f && (this->lastState == MOVING_LEFT || this->lastState == IDLE_LEFT))
            result = true;
        break;
    case IDLE_RIGHT:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f && (this->lastState == MOVING_RIGHT || this->lastState == IDLE_RIGHT))
            result = true;
        break;
    case MOVING_LEFT:
        if (this->velocity.x < 0.f)
            result = true;
        break;
    case MOVING_RIGHT:
        if (this->velocity.x > 0.f)
            result = true;
        break;
    case MOVING_UP:
        if (this->velocity.y < 0.f)
            result = true;
        break;
    case MOVING_DOWN:
        if (this->velocity.y > 0.f)
            result = true;
        break;
    case MOVING:
        if (this->velocity.y != 0 || this->velocity.x != 0)
            result = true;
        break;
    }
    if (result)
    {
        this->lastState = state;
        return true;
    }
    return false;
}