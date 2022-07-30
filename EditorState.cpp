#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void EditorState::updateButtons()
{
    // Updates all buttons in this state and hnaldes their functionality

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    // on button event:
}

void EditorState::updateInput(const float& dt)
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

void EditorState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void EditorState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->renderButtons(target);



    if (this->debug == true)
    {
        this->renderDebug(target);
    }
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

// Init functions
void EditorState::initKeybinds()
{
    // Keybinds in the game state (so while you are playing)
    ifstream ifs("Config/editorstate_keybinds.ini");
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

void EditorState::initFonts()
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

void EditorState::initBackground()
{
}

void EditorState::initVariables()
{

}

void EditorState::initButtons()
{

}

void EditorState::renderDebug(sf::RenderTarget* target)
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
