#include "Player.h"

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 17.f, 16.f, 12.f, 14.f);
    this->createMovementComponent(300.f, 15.f, 5.f); // maxSpeed, acceleration, deceleration
    this->createAnimationComponent(texture_sheet);

    this->setScale(10.f);
    
    this->animationComponent->addAnimation("IDLE_RIGHT", 60.f, 0, 3, 1, 3, 48, 48);
    this->animationComponent->addAnimation("IDLE_LEFT",  60.f, 0, 2, 1, 2, 48, 48);
    this->animationComponent->addAnimation("IDLE_UP",    60.f, 0, 1, 1, 1, 48, 48);
    this->animationComponent->addAnimation("IDLE_DOWN",  60.f, 0, 0, 1, 0, 48, 48);
    this->animationComponent->addAnimation("WALK_LEFT",  20.f, 2, 2, 3, 2, 48, 48);
    this->animationComponent->addAnimation("WALK_RIGHT", 20.f, 2, 3, 3, 3, 48, 48);
    this->animationComponent->addAnimation("WALK_DOWN",  20.f, 2, 0, 3, 0, 48, 48);
    this->animationComponent->addAnimation("WALK_UP",    20.f, 2, 1, 3, 1, 48, 48);
                                                            //sx,sy,ex,ey,  w,  h

}

Player::~Player()
{

}

// Functions
void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->getState(MOVING_UP))
        this->animationComponent->play("WALK_UP", dt);
    else if (this->movementComponent->getState(MOVING_DOWN))
        this->animationComponent->play("WALK_DOWN", dt);
    else if (this->movementComponent->getState(IDLE_LEFT))
        this->animationComponent->play("IDLE_LEFT", dt);
    else if (this->movementComponent->getState(IDLE_RIGHT))
        this->animationComponent->play("IDLE_RIGHT", dt);
    else if (this->movementComponent->getState(IDLE_DOWN))
        this->animationComponent->play("IDLE_DOWN", dt);
    else if (this->movementComponent->getState(IDLE_UP))
        this->animationComponent->play("IDLE_UP", dt);
    else if (this->movementComponent->getState(MOVING_LEFT))
        this->animationComponent->play("WALK_LEFT", dt);
    else if (this->movementComponent->getState(MOVING_RIGHT))
        this->animationComponent->play("WALK_RIGHT", dt);
        
    this->hitboxComponent->update();
}