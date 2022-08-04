#include "Game.h"

// Init functions
void Game::initWindow()
{
    // create SFML Window using Config file

    ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool v_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        string key = "";
        ifs >> key;
        getline(ifs, title);
        ifs >> key >> window_bounds.width >> window_bounds.height;
        ifs >> key >> fullscreen;
        ifs >> key >> framerate_limit;
        ifs >> key >> v_sync_enabled;
        ifs >> key >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(v_sync_enabled);
}

void Game::initKeys()
{
    // List of all Key available
    ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open())
    {
        string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
        
    }
    ifs.close();
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initVariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;

    // Fps Calculator:
    this->updateClock.restart();
    this->fpsText.setString("Fps: " + to_string((int)this->fps));
    this->fpsText.setCharacterSize(15);
    this->fpsText.setPosition(10, 10);
    this->fpsText.setFont(this->font);

    if (!this->font.loadFromFile("Fonts/Roboto-Bold.ttf"))
        throw("Could not load font (in Game::initVariables)");
}



void Game::initGlobalKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/global_keybinds.ini");
    if (ifs.is_open())
    {
        string key = "", key_value = "";
        while (ifs >> key >> key_value)
        {
            this->globalKeybinds[key] = this->supportedKeys.at(key_value);
            this->isHold[key] = false;
        }
        
    }
    ifs.close();
}
// Constructors/Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initGlobalKeybinds();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game::updateSFMLEvents() 
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
        
    }
    
}

void Game::update() 
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->globalKeybinds.at("SHOW_FPS"))))
    {
        if (!this->isHold["SHOW_FPS"])
            this->showFps = !this->showFps;
        this->isHold["SHOW_FPS"] = true;
    }
    else
        this->isHold["SHOW_FPS"] = false;
}

void Game::render() 
{
    this->window->clear();

    // Render items
    if (!this->states.empty())
        this->states.top()->render();
    
    if (this->showFps)
        this->renderFps();

    this->window->display();
}

void Game::run() 
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::updateDt()
{
    // Updates the dt var (Deltatime) with the time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication()
{
    cout << "Ending Application!" << endl;
}

void Game::renderFps()
{
    // Calculate;
    this->fps = 1.f / this->dt;

    if (this->updateClock.getElapsedTime().asMilliseconds() > 1000)
    {
        this->fpsText.setString("Fps: " + to_string((int)this->fps));
        this->updateClock.restart();
    }

    this->window->draw(fpsText);
}
