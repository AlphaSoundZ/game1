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
        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0;
    }
    else if (this->velocity.x < 0.f)
    {
        // Deceleration x negative
        this->velocity.x += deceleration;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0;
    }
    if (this->velocity.y > 0.f)
    {
        // Deceleration y positive
        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0;
    }
    else if (this->velocity.y < 0.f)
    {
        // Deceleration y negative
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0;
    }
    // Max velocity check
    if (this->velocity.y > this->maxVelocity)
        this->velocity.y = this->maxVelocity;
    if (this->velocity.y < -this->maxVelocity)
        this->velocity.y = -this->maxVelocity;
    if (this->velocity.x > this->maxVelocity)
        this->velocity.x = this->maxVelocity;
    if (this->velocity.x < -this->maxVelocity)
        this->velocity.x = -this->maxVelocity;

    if (this->sprite.getPosition().y < 0)
        this->velocity.y = -this->velocity.y;
    if (this->sprite.getPosition().y >(1080-this->sprite.getGlobalBounds().height))
        this->velocity.y = -this->velocity.y;
    if (this->sprite.getPosition().x < 0)
        this->velocity.x = -this->velocity.x;
    if (this->sprite.getPosition().x >(1920-this->sprite.getGlobalBounds().width))
        this->velocity.x = -this->velocity.x;

    // Final move
    this->sprite.move(this->velocity * dt); // Uses velocity
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}
