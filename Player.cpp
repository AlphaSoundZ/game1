#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariables();

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

// Init functions
void Player::initVariables()
{

}

// Functions
void Player::update(const float& dt)
{
    this->movementComponent->update(dt);

    this->animationComponent->play("IDLE_RIGHT", dt);
}