#include "State.h"

State::State(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
{
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->quit = false;
}

State::~State()
{

}

const bool & State::getQuit() const
{
    return this->quit;
}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->isKeyHold["CLOSE"] = true;
    else
    {
        if (this->isKeyHold["CLOSE"])
            this->quit = true;
        this->isKeyHold["CLOSE"] = false;
    }
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}