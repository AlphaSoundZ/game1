#include "GameState.h"

// Constructor / destructor
GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initFonts();
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState()
{
    delete this->player;
}

// Update
void GameState::updateInput(const float& dt)
{
    // Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    
    // Quit game state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->isHold["CLOSE"] = true;
    else
    {
        if (this->isHold["CLOSE"])
            this->endState();
        this->isHold["CLOSE"] = false;
    }

    // Toggle debug
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DEBUG"))))
    {
        if (!this->isHold["DEBUG"])
            this->debug = (this->debug) ? false : true;
        this->isHold["DEBUG"] = true;
    }
    else
        this->isHold["DEBUG"] = false;
}

void GameState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->player->update(dt, this->mousePosView);
}


// Render
void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->player->render(*target);
    if (this->debug)
        this->renderDebug(target);
}

// Init functions
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
            this->isHold[key] = false;
        }
        
    }
    ifs.close();
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/BASKVILL.ttf"))
    {
        throw("File missing! - Could not load font (in MainMenuState::initFonts)");
    }
    if (!this->robotoFont.loadFromFile("Fonts/Roboto-Bold.ttf"))
    {
        throw("File missing! - Could not load font (in MainMenuState::initFonts)");
    }
}

void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Ressources/Images/Sprites/Player/player_sheet.png"))
        throw("File missing! - Could not load player texture (in GameState::initTextures)");
}

void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::renderDebug(sf::RenderTarget* target)
{
        sf::Text mouseText;
        mouseText.setPosition(this->mousePosView.x+10, this->mousePosView.y-15);
        mouseText.setFont(this->robotoFont);
        mouseText.setFillColor(sf::Color::White);
        mouseText.setCharacterSize(12);
        stringstream ss;
        ss << this->mousePosView.x << " " << this->mousePosView.y;
        mouseText.setString(ss.str());

        target->draw(mouseText);
}