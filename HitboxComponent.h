#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class HitboxComponent
{
private:
    sf::RectangleShape hitbox;
    sf::Sprite& sprite;

    float offsetX, offsetY;

public:
    HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

    // Functions
    bool checkIntersect(const sf::FloatRect& frect);
    void setScale(const float scale);

    void update();
    void render(sf::RenderTarget& target);
};

#endif