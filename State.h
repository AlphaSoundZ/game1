#ifndef STATE_H
#define STATE_H

#pragma once

#include "Entity.h"

using namespace std;

class State
{
private:


protected:
    sf::RenderWindow* window;
    map<string, int>* supportedKeys;
    map<string, int> keybinds;
    bool quit;

    // Ressources
    vector<sf::Texture> textures;

    // Functions

    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow* window, map<string, int>* supportedKeys);
    virtual ~State();

    const bool & getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;
    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif