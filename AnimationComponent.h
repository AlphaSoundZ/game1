#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#pragma once

#include <map>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class AnimationComponent
{
private:
    class Animation
    {
        public:
        // Variables
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer, timer;
        int width, height;
        sf::IntRect startRect, currentRect, endRect;
        
        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
            float animation_timer, 
            int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
            : sprite(sprite), textureSheet(texture_sheet), 
                animationTimer(animation_timer), width(width), height(height)
        {
            this->timer = 0.f;
            this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
            this->sprite.setScale(3.f, 3.f);
        }

        // Functions
        void play(const float& dt)
        {
            // Update timer
                this->timer += 100.f * dt;
            if (this->timer >= this->animationTimer)
            {
                // Reset timer
                this->timer = 0.f;

                // Move to next frame
                if (this->currentRect != this->endRect)
                {
                    this->currentRect.left += this->width;
                }
                else // Go to first frame
                {
                    this->currentRect.left = this->startRect.left;
                }

                this->sprite.setTextureRect(this->currentRect);

            }
        }
        void reset()
        {
            this->timer = 0.f;
            this->currentRect = this->startRect;
        }
    };


public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    map<string, Animation*> animations;

    // Functions
    void addAnimation(const string key,  
        float animation_timer, 
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    void play(const string key, const float& dt);
};

#endif