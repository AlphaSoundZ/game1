#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include "State.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    // Variables
    bool debug = false;
    sf::Font font, robotoFont;

    PauseMenu pauseMenu;
    
    Player* player;

    // Functions

    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~GameState();

    // Functions

    // Update
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render
    void render(sf::RenderTarget* target = nullptr);
    void renderDebug(sf::RenderTarget* target = nullptr);
};

#endif