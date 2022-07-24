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

    map<string, Button*> buttons;

    // Functions
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~MainMenuState();

    // Functions
    void endState();

    // Update
    void updateButtons();
    void updateInput(const float& dt);
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);

    // Render
    void render(sf::RenderTarget* target = nullptr);
};

#endif