#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#pragma once

#include "MainMenuState.h"
#include "Button.h"

class SettingsState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font robotoFont;
    map<string, bool> isKeyHold;

    bool debug = false;

    map<string, Button*> buttons;

    // Functions
    void initVariables();
    void initFonts();
    void initBackground();
    void initKeybinds();
    void initButtons();

public:
    SettingsState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~SettingsState();

    // Functions

    // Update
    void updateButtons();
    void updateInput(const float& dt);
    void update(const float& dt);
    
    // Render
    void renderButtons(sf::RenderTarget* target = nullptr);
    void renderDebug(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif