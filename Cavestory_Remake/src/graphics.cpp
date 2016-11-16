//
//  Graphics.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/1/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics()
{
    if (SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HIGHT, 0, &_window, &_renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
    
    SDL_SetWindowTitle(_window, "Cavestory Remake");
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
    if(_spriteSheets.count(filePath) == 0)
    {
        _spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    
    return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture *source, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle)
{
    SDL_RenderCopy(_renderer, source, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
    SDL_RenderPresent(_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
    return _renderer;
}
