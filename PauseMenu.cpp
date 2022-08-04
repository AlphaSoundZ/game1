#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, bool* paused_ptr)
{
    this->paused = &paused_ptr;
    this->window = &window;
    cout << paused_ptr << endl;
    cout << this->paused << endl;

    this->initFonts();

    // Background
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x), 
            static_cast<float>(window.getSize().y)
        )
    );
    this->background.setFillColor(sf::Color(20, 20, 20, 80));

    // Container
    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 3.f, 
            static_cast<float>(window.getSize().y) / 3.f
        )
    );
    this->container.setFillColor(sf::Color(20, 20, 20, 200));

    this->container.setPosition(
        (static_cast<float>(window.getSize().x) - this->container.getSize().x) / 2.f, 
        (static_cast<float>(window.getSize().y) - this->container.getSize().y) / 2.f
    );

    this->initButtons(window);
}

PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Functions
void PauseMenu::render(sf::RenderTarget* target)
{
    target->draw(background);
    target->draw(container);

    this->renderButtons(target);
}

void PauseMenu::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}

void PauseMenu::update(const float& dt)
{
    this->updateButtons();
}

void PauseMenu::initButtons(sf::RenderWindow& window)
{
    int topButton[4] = {static_cast<int>(window.getSize().x)/2, static_cast<int>(window.getSize().y)/2-70, 300, 50}, distance = 20, nth_btn = 0;

    this->buttons["UNPAUSE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], // pos, size
        &this->font, "Resume", // text
        28, 33, 33, // text size
        sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), // text color
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200)); // bg color
    nth_btn++;
    this->buttons["KEYBOARD_CONTROLS"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Keyboard Controls", 
        28, 33, 33, 
        sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
    nth_btn++;
    this->buttons["EXIT_STATE"] = new Button(topButton[0], topButton[1]+topButton[3]*nth_btn+distance*nth_btn, topButton[2], topButton[3], 
        &this->font, "Exit", 
        28, 33, 33, 
        sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255),
        sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 50), sf::Color(150, 150, 150, 200));
}

void PauseMenu::updateButtons()
{
    // Updates all buttons and handles their functionality

    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    for (auto &it : this->buttons)
    {
        it.second->update(mousePosView);
    }

    // on button event:
    // quit the game
    if (this->buttons["EXIT_STATE"]->isPressed())
        cout << "EXIT!" << endl;
    if (this->buttons["UNPAUSE"]->isPressed())
        this->set();
    if (this->buttons["KEYBOARD_CONTROLS"]->isPressed())
    {
        system("C:\\Users\\janja\\Documents\\GIthubRepos\\game1\\Config\\gamestate_keybinds.ini");
    }
    cout << this->paused << endl;
}

void PauseMenu::initFonts()
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

void PauseMenu::set()
{
    **this->paused = false;
}