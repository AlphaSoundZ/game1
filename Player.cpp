#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariables();

    this->setPosition(x, y);

    this->createMovementComponent(300.f, 15.f, 5.f); // maxSpeed, acceleration, deceleration
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 13, 0, 64, 64);
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

    this->animationComponent->play("IDLE_LEFT", dt);
}