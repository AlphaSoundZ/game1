#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#pragma once

#include "State.h"
#include "Button.h"

class EditorState
    : public State
{
// Variables
    sf::RectangleShape background;
    sf::Font font;
    sf::Font robotoFont;
    map<string, bool> isHold;

    bool debug = false;

    map<string, Button*> buttons;

    // Functions
    void initVariables();
    void initFonts();
    void initBackground();
    void initKeybinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~EditorState();

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