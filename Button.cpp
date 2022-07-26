#include "Button.h"

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, string text, 
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    
    this->button_state = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(24);

    this->shape.setOrigin(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
    this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));

    

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

// Accessors
const bool Button::isPressed() const
{
    if (this->button_state == BTN_RELEASED)
        return true;
    return false;
}

// Functions
void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos)
{    
    // Updates the booleans for hover and pressed

    // If drag button show HOVER as soon as release show IDLE
    if ((this->button_state == BTN_ACTIVE || this->button_state == BTN_HOVER) && !this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->button_state = BTN_HOVER;
    else
        this->button_state = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->button_state = BTN_HOVER;

        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->button_state = BTN_ACTIVE;
            this->isKeyHold["BUTTON"] = true;
        }
        else
        {
            if (this->isKeyHold["BUTTON"])
                this->button_state = BTN_RELEASED;
            this->isKeyHold["BUTTON"] = false;
        }
        
        
    }
    else
        this->isKeyHold["BUTTON"] = false;




    switch (this->button_state)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    case BTN_RELEASED:
        this->shape.setFillColor(this->idleColor);
        break;
    
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}