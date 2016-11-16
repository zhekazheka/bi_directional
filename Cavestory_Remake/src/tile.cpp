//
//  tile.cpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 16/11/2016.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "tile.hpp"
#include "graphics.h"

#include <SDL2/SDL.h>

Tile::Tile()
{
    
}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position)
    :   _tileset(tileset),
        _size(size),
        _tilesetPosition(tilesetPosition),
        _position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE))
{
    
}

void Tile::update(int elapsedTime)
{
    
}

void Tile::draw(Graphics &graphics)
{
    SDL_Rect destRect = { _position.x, _position.y,
                        static_cast<int>(_size.x * globals::SPRITE_SCALE),
                        static_cast<int>(_size.y  * globals::SPRITE_SCALE) };
    
    SDL_Rect sourceRect = { _tilesetPosition.x, _tilesetPosition.y, _size.x, _size.y };
    
    graphics.blitSurface(_tileset, &sourceRect, &destRect);
}
