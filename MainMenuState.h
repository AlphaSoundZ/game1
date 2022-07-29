#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font robotoFont;

    Entity idlePlayer;
    sf::Texture textureSheet;
    
    map<string, bool> isHold;
    

    string idlePlayerState;

    bool debug = false;

    map<string, Button*> buttons;

    // Functions
    void initVariables();
    void initFonts();
    void initBackground();
    void initKeybinds();
    void initButtons();
    void initIdlePlayer();

public:
    MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~MainMenuState();

    // Functions

    // Update
    void updateButtons();
    void updateIdlePlayer();
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render
    void renderButtons(sf::RenderTarget* target = nullptr);
    void renderDebug(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif