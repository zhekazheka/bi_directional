//
//  animatedsprite.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/29/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "animatedsprite.hpp"
#include "graphics.h"

AnimatedSprite::AnimatedSprite()
{
    
}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
                               float posX, float posY, float timeToUpdate) :
            Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
            _timeElapsed(0),
            _frameIndex(0),
            _timeToUpdate(timeToUpdate),
            _isVisible(true),
            _currentAnimationOnce(false),
            _currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
    std::vector<SDL_Rect> rectangles;
    
    for (int i = 0; i < frames; ++i)
    {
        SDL_Rect newRect = {(i + x) * width, y, width, height};
        rectangles.push_back(newRect);
    }
    
    _animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
    _offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimation()
{
    _animations.clear();
    _offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
    _currentAnimationOnce = once;
    
    if(_currentAnimation != animation)
    {
        _currentAnimation = animation;
        _frameIndex = 0;
    }
}

void AnimatedSprite::stopAnimation()
{
    _frameIndex = 0;
    animationDone(_currentAnimation);
}

void AnimatedSprite::setVisible(bool visible)
{
    _isVisible = visible;
}

void AnimatedSprite::update(int elapsedTime)
{
    Sprite::update();
    
    _timeElapsed += elapsedTime;
    if(_timeElapsed > _timeToUpdate)
    {
        _timeElapsed -= _timeToUpdate;
        if(_frameIndex < _animations[_currentAnimation].size() - 1)
        {
            ++_frameIndex;
        }
        else
        {
            if(_currentAnimationOnce)
            {
                setVisible(false);
            }
            _frameIndex = 0;
            animationDone(_currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
    if(_isVisible)
    {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + _offsets[_currentAnimation].x;
        destinationRectangle.y = y + _offsets[_currentAnimation].y;
        destinationRectangle.w = _sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = _sourceRect.h * globals::SPRITE_SCALE;
        
        SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex];
        graphics.blitSurface(_spriteSheet, &sourceRect, &destinationRectangle);
    }
}
