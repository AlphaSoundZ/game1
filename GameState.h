#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include "State.h"

class GameState :
    public State
{
private:
    Entity player;

    // Functions

    void initKeybinds();

public:
    GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~GameState();

    // Functions
    void endState();

    // Update
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render
    void render(sf::RenderTarget* target = nullptr);
};

#endif