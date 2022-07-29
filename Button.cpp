#include "Button.h"

Button::Button(float x, float y, float width, float height, 
        sf::Font* font, string text,
        unsigned text_idle_size, unsigned text_hover_size, unsigned text_active_size,
        sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
        sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    
    this->button_state = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(text_idle_size);

    this->shape.setOrigin(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);

    this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
    this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));

    

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;
    this->textIdleSize = text_idle_size;
    this->textHoverSize = text_hover_size;
    this->textActiveSize = text_active_size;

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
            this->isHold["BUTTON"] = true;
        }
        else
        {
            if (this->isHold["BUTTON"])
                this->button_state = BTN_RELEASED;
            this->isHold["BUTTON"] = false;
        }
        
        
    }
    else
        this->isHold["BUTTON"] = false;




    switch (this->button_state)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        this->text.setCharacterSize(this->textIdleSize);
        this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
        this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->text.setCharacterSize(this->textHoverSize);
        this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
        this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->text.setCharacterSize(this->textActiveSize);
        this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
        this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
        break;
    case BTN_RELEASED:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        this->text.setCharacterSize(this->textIdleSize);
        this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
        this->text.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y - static_cast<float>(this->text.getCharacterSize()) / 4.f));
        break;
    
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }
}