#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void SettingsState::updateButtons()
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
    if (this->buttons["KEYBOARD_CONTROLS"]->isPressed())
    {
        system("C:\\Users\\janja\\Documents\\GIthubRepos\\game1\\Config\\gamestate_keybinds.ini");
    }
}

void SettingsState::updateInput(const float& dt)
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
    
    // Quit game state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->isHold["CLOSE"] = true;
    else
    {
        if (this->isHold["CLOSE"])
            this->endState();
        this->isHold["CLOSE"] = false;
    }
        
}

void SettingsState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);
    this->renderButtons(target);



    if (this->debug == true)
    {
        this->renderDebug(target);
    }
}

void SettingsState::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}

// Init functions
void SettingsState::initKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/settingsstate_keybinds.ini");
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

void SettingsState::initFonts()
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

void SettingsState::initBackground()
{
    this->background.setSize(
        sf::Vector2f
        (
            static_cast<float>(this->window->getSize().x), 
            static_cast<float>(this->window->getSize().y)
        )
    );

    if (!this->backgroundTexture.loadFromFile("Ressources/Images/Backgrounds/settings_bg1.png"))
        throw("File missing! - Could not load Ressource (in MainMenuState::initBackground)");
    
    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initVariables()
{

}

void SettingsState::initButtons()
{
    int topButton[4] = {267, 500, 300, 50}, distance = 20, nth_btn = 0;

    this->buttons["SETTINGS_FRAMERATE_LIMIT"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Framerate limit", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["KEYBOARD_CONTROLS"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Keyboard Controls", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["EXIT_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Go Back", 
        28, 33, 33, 
        sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
}

void SettingsState::renderDebug(sf::RenderTarget* target)
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
