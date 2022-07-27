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

class MovementComponent
{
private:
    // Variables

    sf::Sprite& sprite;
    
    float maxVelocity, acceleration, deceleration;
    sf::Vector2f velocity;

    // Init functions

public:
    MovementComponent(sf::Sprite& sprite, 
        float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    // Accessors
    const sf::Vector2f& getVelocity() const;
    
    // Functions
    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);
};

#endif