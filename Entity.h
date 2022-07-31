#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;

public:
    AnimationComponent* animationComponent;

    Entity();
    virtual ~Entity();

    // Component functions
    void setTexture(sf::Texture& texture);
    void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);

    // Accessors
    bool contains(sf::Vector2f mouse_pos);
    
    // Functions
    virtual void setPosition(const float x, const float y);
    virtual void setScale(const float scale);
    virtual void move(const float x, const float y, const float& dt);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);
};

#endif