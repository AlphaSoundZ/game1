#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
    // Variables
    sf::RectangleShape background;
    sf::Font font;

    Button* gamestate_btn;

    // Functions
    void initFonts();
    void initKeybinds();

public:
    MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys);
    virtual ~MainMenuState();

    // Functions
    void endState();

    // Update
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render
    void render(sf::RenderTarget* target = nullptr);
};

#endif