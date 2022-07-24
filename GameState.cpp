#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
}

GameState::~GameState()
{

}

void GameState::endState()
{
    cout << "Ending GameState!" << endl;
}

void GameState::updateInput(const float& dt)
{
    this->checkForQuit();

    // Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt, 0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt, -1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt, 0.f, 1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt, 1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->quit = true;
}

void GameState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    this->player.render(target);
}

void GameState::initKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/gamestate_keybinds.ini");
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