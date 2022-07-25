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

void State::endState()
{
    this->quit = true;
}

const bool & State::getQuit() const
{
    return this->quit;
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}