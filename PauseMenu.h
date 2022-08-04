#ifndef PAUSEMENU_H
#define PAUSEMENU_H

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

#include "Button.h"

class PauseMenu
{
private:
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Font font;
    sf::Font robotoFont;

    sf::Vector2f mousePosView;
    
    map<string, bool> isHold;

    bool debug = false;

    map<string, Button*> buttons;

    sf::RenderWindow* window;

    bool** paused;
    
    void initButtons(sf::RenderWindow& window);
    void initFonts();
public:
    PauseMenu(sf::RenderWindow& window, bool* paused_ptr);
    virtual ~PauseMenu();

    // Functions:

    void update(const float& dt);
    void updateButtons();
    void render(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget* target);

    void set();
};

#endif