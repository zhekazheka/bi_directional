//
//  animatedtile.cpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 31/01/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "animatedtile.hpp"
#include "graphics.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPositions, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position)
    : Tile(tileset, size, tilesetPositions.at(0), position),
    _tilesetPositions(tilesetPositions),
    _duration(duration),
    _tileToDraw(0)
{
    
}

void AnimatedTile::update(float elapsedTime)
{
    if(_amountOfTime <= 0)
    {
        if(_tileToDraw == _tilesetPositions.size() - 1)
        {
            _tileToDraw = 0;
        }
        else
        {
            ++_tileToDraw;
        }
        
        _amountOfTime = _duration;
    }
    else
    {
        _amountOfTime -= elapsedTime;
    }
    
    Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics &graphics)
{
    SDL_Rect destRect = { _position.x, _position.y, static_cast<int>(_size.x * globals::SPRITE_SCALE), static_cast<int>(_size.y  * globals::SPRITE_SCALE) };
    SDL_Rect sourceRect = { _tilesetPositions.at(_tileToDraw).x, _tilesetPositions.at(_tileToDraw).y, _size.x, _size.y };
    
    graphics.blitSurface(_tileset, &sourceRect, &destRect);
    
}
