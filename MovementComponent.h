#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

enum movement_states { IDLE = 0, IDLE_DOWN, IDLE_UP, IDLE_LEFT, IDLE_RIGHT, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN, MOVEMENT_LOCKED };

class MovementComponent
{
private:
    // Variables

    sf::Sprite& sprite;
    
    float maxVelocity, acceleration, deceleration;
    sf::Vector2f velocity;

    short unsigned lastState;

    // Init functions

public:
    MovementComponent(sf::Sprite& sprite, 
        float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    bool movementLocked = false;

    // Accessors
    const sf::Vector2f& getVelocity() const;
    const float getMaxVelocity() const;
    const bool getState(const short unsigned state);
    
    // Functions
    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);
};

#endif