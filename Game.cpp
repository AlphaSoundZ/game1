#include "Game.h"

// Static functions

// Init functions
void Game::initWindow()
{
    // create SFML Window using Config file

    ifstream ifs("Config/window.ini");

    string title = "None";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 120;
    bool v_sync_enabled = false;

    if (ifs.is_open())
    {
        getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> v_sync_enabled;
    }

    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title);
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys));
    this->states.push(new GameState(this->window, &this->supportedKeys));
}
// Constructors/Destructors
Game::Game()
{
    this->initWindow();
    this->initKeys();
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

}

void Game::render() 
{
    this->window->clear();

    // Render items
    if (!this->states.empty())
        this->states.top()->render();
    

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
