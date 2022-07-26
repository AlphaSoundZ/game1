#ifndef BUTTON_H
#define BUTTON_H

#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_RELEASED};

class Button
{
private:
    short unsigned button_state;
    map<string, bool> isKeyHold;


public:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    Button(float x, float y, float width, float height, 
        sf::Font* font, string text, 
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    virtual ~Button();
    // Accessors
    const bool isPressed() const;

    // Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};

#endif