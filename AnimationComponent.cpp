#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }
}

void AnimationComponent::play(const string key, const float& dt, const float& modifier_percentage, const bool priority) // modifier_percentage standard value is 1 (100%)
{
    if (this->priorityAnimation)
    {
        if (this->priorityAnimation == this->animations[key] && this->priorityAnimation->isPlaying()) // play priority animation
        {
            if (this->lastAnimation != this->animations[key] && this->lastAnimation != NULL)
                this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
            
            this->animations[key]->play(dt, modifier_percentage);
        }

        if (!this->priorityAnimation->isPlaying())
        {
            this->priorityAnimation = NULL;
        }
    }
    else if (priority) // set new priority animation
    {
        if (this->lastAnimation != this->animations[key] && this->lastAnimation != NULL)
            this->lastAnimation->reset();
        this->lastAnimation = this->animations[key];
        this->priorityAnimation = this->animations[key];
        this->animations[key]->play(dt, modifier_percentage);
    }
    else // no priority exits. Play requested animation
    {
        if (this->lastAnimation != this->animations[key] && this->lastAnimation != NULL)
            this->lastAnimation->reset();
        this->lastAnimation = this->animations[key];
        this->animations[key]->play(dt, modifier_percentage);
    }
}

void AnimationComponent::addAnimation(const string key,
    float animation_timer, 
    int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
    this->animations[key] = new Animation(
        this->sprite, 
        this->textureSheet, animation_timer, 
        start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

bool AnimationComponent::isPlaying(const string key)
{
    return this->animations[key]->isPlaying();
}
