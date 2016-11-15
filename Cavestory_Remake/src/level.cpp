//
//  Level.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 11/8/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "level.hpp"
#include "graphics.h"

#include <SDL2/SDL.h>

namespace level_constants {
    const std::string LEVEL_SPRITE_SHEET = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/backgrounds/bkBlue.png";
}


Level::Level()
{
    
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
            _mapName(mapName),
            _spawnPoint(spawnPoint),
            _size(Vector2(0, 0))
{
    this->loadMap(mapName, graphics);
}

Level::~Level()
{
    
}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
    // TEMPORARY CODE TO LOAD BACKGROUND
    _backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(level_constants::LEVEL_SPRITE_SHEET));
    
    _size = Vector2(1280, 960);
}

void Level::update(float elapsedTime)
{
    
}

void Level::draw(Graphics &graphics)
{
    // Draw the background
    SDL_Rect sourceRect = { 0, 0, 64, 64 };
    SDL_Rect destRect;
    
    for (int x = 0; x < _size.x / 64.0f; ++x)
    {
        for (int y = 0; y < _size.y / 64.0f; ++y)
        {
            destRect.x = x * 64 * globals::SPRITE_SCALE;
            destRect.y = y * 64 * globals::SPRITE_SCALE;
            destRect.w = 64 * globals::SPRITE_SCALE;
            destRect.h = 64 * globals::SPRITE_SCALE;
            
            graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
        }
    }
}
