#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 0.f, 0.f, 73.f, 73.f);
    this->createMovementComponent(300.f, 15.f, 5.f); // maxSpeed, acceleration, deceleration
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_RIGHT", 20.f, 0, 0, 3, 0, 73, 73);
    this->animationComponent->addAnimation("IDLE_LEFT", 20.f, 0, 1, 3, 1, 73, 73);
    this->animationComponent->addAnimation("WALK_RIGHT", 20.f, 0, 2, 3, 2, 73, 73);
    this->animationComponent->addAnimation("WALK_LEFT", 20.f, 0, 3, 3, 3, 73, 73);

    this->setScale(3.f);
}

Player::~Player()
{

}

// Functions
void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->getState(IDLE))
        this->animationComponent->play("IDLE_LEFT", dt);
    else if (this->movementComponent->getState(MOVING_LEFT))
        this->animationComponent->play("WALK_LEFT", dt);
    else if (this->movementComponent->getState(MOVING_RIGHT))
        this->animationComponent->play("WALK_RIGHT", dt);
    
    this->hitboxComponent->update();
}