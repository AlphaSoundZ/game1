#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initIdlePlayer();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Update functions
void MainMenuState::updateButtons()
{
    // Updates all buttons in this state and hnaldes their functionality

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    // on button event:
    // quit the game
    if (this->buttons["EXIT_STATE"]->isPressed())
        this->endState();
    // new game
    if (this->buttons["GAME_STATE"]->isPressed())
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    if (this->buttons["SETTINGS_STATE"]->isPressed())
        this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
}

void MainMenuState::updateInput(const float& dt)
{
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

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
    this->updateIdlePlayer();

    this->idlePlayer.animationComponent->play(this->idlePlayerState, dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);
    this->renderButtons(target);

    this->idlePlayer.render(target);

    if (this->debug == true)
    {
        this->renderDebug(target);
    }
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

// Functions
void MainMenuState::updateIdlePlayer()
{
    //this->idlePlayerState = "IDLE";
    if (this->idlePlayer.contains(this->mousePosView))
    {
        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->isHold["IDLEPLAYER"] = true;
        }
        else
        {
            if (this->isHold["IDLEPLAYER"])
            {
                this->idlePlayerState = (this->idlePlayerState == "IDLE") ? "ACTION" : "IDLE";
            }
            this->isHold["IDLEPLAYER"] = false;
        }
        
        
    }
    else
        this->isHold["IDLEPLAYER"] = false;
}

// Init functions
void MainMenuState::initKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/mainmenustate_keybinds.ini");
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

void MainMenuState::initFonts()
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

void MainMenuState::initBackground()
{
    this->background.setSize(
        sf::Vector2f
        (
            static_cast<float>(this->window->getSize().x), 
            static_cast<float>(this->window->getSize().y)
        )
    );

    if (!this->backgroundTexture.loadFromFile("Ressources/Images/Backgrounds/mainmenu_bg1.png"))
        throw("File missing! - Could not load Ressource (in MainMenuState::initBackground)");
    
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initVariables()
{
    this->idlePlayerState = "IDLE";
}

void MainMenuState::initButtons()
{
    float topButton[4] = {707, 450, 300, 50}, distance = 20, nth_btn = 0;
    this->buttons["GAME_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "New Game", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["SETTINGS_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Settings", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["EDITOR_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Editor", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), 
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["EXIT_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Quit", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), 
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));

}

void MainMenuState::initIdlePlayer()
{
    this->idlePlayerState = "IDLE";

    // Player Animation on MainMenu Screen
    if (!textureSheet.loadFromFile("Ressources/Images/Sprites/Player/player_sheet.png"))
        throw("File missing! - Could not load player texture (in GameState::initTextures)");
    this->idlePlayer.setTexture(textureSheet);
    this->idlePlayer.createAnimationComponent(textureSheet);
    this->idlePlayer.animationComponent->addAnimation("IDLE", 20.f, 0, 0, 3, 0, 73, 73);
    this->idlePlayer.animationComponent->addAnimation("ACTION", 20.f, 0, 1, 3, 1, 73, 73);
    this->idlePlayer.setPosition(1128, 335);
    this->idlePlayer.setScale(7.f);
}

void MainMenuState::renderDebug(sf::RenderTarget* target)
{
        sf::Text mouseText;
        mouseText.setPosition(this->mousePosView.x+10, this->mousePosView.y-15);
        mouseText.setFont(this->robotoFont);
        mouseText.setFillColor(sf::Color::Black);
        mouseText.setCharacterSize(12);
        stringstream ss;
        ss << this->mousePosView.x << " " << this->mousePosView.y;
        mouseText.setString(ss.str());

        target->draw(mouseText);
}