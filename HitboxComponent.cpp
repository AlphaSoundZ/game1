#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
    float offset_x, float offset_y, 
    float width, float height)
    : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineColor(sf::Color(155, 128, 255));
    this->hitbox.setOutlineThickness(1.f);
}

HitboxComponent::~HitboxComponent()
{

}

void HitboxComponent::update()
{
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
    target.draw(this->hitbox);
}


bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
    return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::setScale(const float scale)
{
    this->hitbox.setSize(sf::Vector2f(this->hitbox.getGlobalBounds().width*scale, this->hitbox.getGlobalBounds().height*scale)); // setScale would increase the border thickness
    // offset changes when changing scale
    this->offsetX *= scale;
    this->offsetY *= scale;
}