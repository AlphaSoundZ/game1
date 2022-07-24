#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    this->initKeybinds();

    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::endState()
{
    cout << "Ending MainMenuState!" << endl;
}

void MainMenuState::updateInput(const float& dt)
{
    this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{

    this->updateInput(dt);

}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);
}

void MainMenuState::initKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/mainmenu_keybinds.ini");
    if (ifs.is_open())
    {
        string key = "", key_value = "";
        while (ifs >> key >> key_value)
        {
            this->keybinds[key] = this->supportedKeys->at(key_value);
        }
        
    }
    ifs.close();
}