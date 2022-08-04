#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
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
void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(background);
    target.draw(container);

    this->renderButtons(target);
}

void PauseMenu::renderButtons(sf::RenderTarget& target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void PauseMenu::update(const float& dt) {
    
}
