#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{

    this->setPosition(x, y);

    this->createMovementComponent(300.f, 15.f, 5.f); // maxSpeed, acceleration, deceleration
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_RIGHT", 20.f, 0, 0, 3, 0, 73, 73);
    this->animationComponent->addAnimation("IDLE_LEFT", 20.f, 0, 1, 3, 1, 73, 73);
    this->animationComponent->addAnimation("WALK_RIGHT", 20.f, 0, 2, 3, 2, 73, 73);
    this->animationComponent->addAnimation("WALK_LEFT", 20.f, 0, 3, 3, 3, 73, 73);
}

Player::~Player()
{

}

// Functions
void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->faceDir(mouse_pos_view) == "LEFT")
    {
        if (this->movementComponent->getVelocity().x == 0.f)
            this->animationComponent->play("IDLE_LEFT", dt);
        else
            this->animationComponent->play("WALK_LEFT", dt);
    }
    if (this->movementComponent->faceDir(mouse_pos_view) == "RIGHT")
    {
        if (this->movementComponent->getVelocity().x == 0.f)
            this->animationComponent->play("IDLE_RIGHT", dt);
        else
            this->animationComponent->play("WALK_RIGHT", dt);
    }
}