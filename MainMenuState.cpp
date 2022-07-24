#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::endState()
{
    cout << "Ending MainMenuState!" << endl;
}

void MainMenuState::updateButtons()
{
    // Updates all buttons in this state and hnaldes their functionality

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    // Quit the game
    if (this->buttons["EXIT_STATE"]->isPressed())
        this->quit = true;
}

void MainMenuState::updateInput(const float& dt)
{
    this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);
    this->renderButtons(target);
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
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

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, 
        &this->font, "New Game", 
        sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
    this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50, 
        &this->font, "Quit", 
        sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}