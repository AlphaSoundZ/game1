#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include "Entity.h"

class Player : public Entity
{
private:

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    // Functions
    virtual void update(const float& dt, sf::Vector2f mouse_pos_view);
};

#endif