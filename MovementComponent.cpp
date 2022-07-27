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
        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0;
    }
    else if (this->velocity.x < 0.f)
    {
        this->velocity.x += deceleration;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0;
    }

    if (this->velocity.y > 0.f)
    {
        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0;
    }
    else if (this->velocity.y < 0.f)
    {
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0;
    }

    // Final move
    this->sprite.move(this->velocity * dt); // Uses velocity
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;

    if (this->velocity.x > this->maxVelocity)
        this->velocity.x = this->maxVelocity;
    else if (-this->velocity.x > this->maxVelocity)
        this->velocity.x = this->maxVelocity*-1;

    if (this->velocity.y > this->maxVelocity)
        this->velocity.y = this->maxVelocity;
    else if (-this->velocity.y > this->maxVelocity)
        this->velocity.y = this->maxVelocity*-1;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}
