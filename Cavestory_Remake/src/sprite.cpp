//
//  sprite.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/6/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "sprite.hpp"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite()
{
    
}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
               int width, int height, float posX, float posY) : _x(posX), _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;
    
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if(this->_spriteSheet == NULL)
    {
        printf("\nError: Unable to load image\n");
    }
    
    _boundingBox = Rectangle(_x, _y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite()
{
    
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destinationRectangle = { x, y, static_cast<int>(this->_sourceRect.w * globals::SPRITE_SCALE),
                                            static_cast<int>(this->_sourceRect.h * globals::SPRITE_SCALE) };
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update()
{
    _boundingBox = Rectangle(_x, _y, _sourceRect.w * globals::SPRITE_SCALE, _sourceRect.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const
{
    return _boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const
{
    int amountRight = abs(_boundingBox.getRight() - other.getLeft());
    int amountLeft = abs(other.getRight() - _boundingBox.getLeft());
    int amountTop = abs(other.getBottom() - _boundingBox.getTop());
    int amountBottom = abs(_boundingBox.getBottom() - other.getTop());
    
    int vals[4] = { amountRight, amountLeft, amountTop, amountBottom };
    int min = vals[0];
    for (int i = 0; i < 4; ++i)
    {
        if(vals[i] < min)
        {
            min = vals[i];
        }
    }
    
    return
        min == amountRight ? sides::RIGHT :
        min == amountLeft ? sides::LEFT :
        min == amountTop ? sides::TOP :
        min == amountBottom ? sides::BOTTOM :
        sides::NONE;
}

