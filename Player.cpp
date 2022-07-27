#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture)
{
    this->initVariables();
    this->initComponents();
    
    this->setTexture(texture);
    this->setPosition(x, y);
}

Player::~Player()
{

}

// Init functions
void Player::initVariables()
{

}

void Player::initComponents()
{
    this->createMovementComponent(250.f, 15.f, 7.f);
}