#ifndef GAME_H
#define GAME_H

#pragma once

#include "SettingsState.h"

using namespace std;

class Game
{
private:
    // Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;

    sf::Clock dtClock;
    float dt;

    stack<State*> states;

    map<string, int> supportedKeys;
    map<string, int> globalKeybinds; // keybinds that work in every state

    map<string, bool> isHold;

    // Fps Calculator
    sf::Clock updateClock;
    float fps;
    sf::Font font;
    sf::Text fpsText;
    bool showFps = false;


    // Init
    void initWindow();
    void initKeys();
    void initStates();
    void initVariables();
    void initGlobalKeybinds();

public:
    // Constructor/Destructor
    Game();
    virtual ~Game();

    // functions

    // Regular
    void endApplication();

    // Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    // Render
    void render();
    void renderFps();

    // Core
    void run();
};

#endif