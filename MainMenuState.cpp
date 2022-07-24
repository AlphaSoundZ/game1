#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    this->initFonts();
    this->initKeybinds();

    this->gamestate_btn = new Button(100, 100, 150, 50, 
    &this->font, "New Game", 
    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
    delete this->gamestate_btn;
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
    this->updateMousePositions();
    this->updateInput(dt);
    
    this->gamestate_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);

    this->gamestate_btn->render(target);
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

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Roboto-Bold.ttf"))
    {
        throw("File missing! - Could not load font (in MainMenuState::initFonts)");
    }
}