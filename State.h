#ifndef STATE_H
#define STATE_H

#pragma once

#include "Player.h"

using namespace std;

class State
{
private:


protected:
    stack<State*>* states;
    sf::RenderWindow* window;
    map<string, int>* supportedKeys;
    map<string, int> keybinds;
    map<string, bool> isHold;
    bool quit;


    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Ressources
    map<string, sf::Texture> textures;

    // Functions

    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~State();

    const bool & getQuit() const;

    void endState();
    virtual void updateMousePositions();
    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif