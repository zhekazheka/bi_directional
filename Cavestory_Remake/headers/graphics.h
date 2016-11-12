//
//  Graphics.h
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/1/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef GRAPHICS_h
#define GRAPHICS_h

#include <SDL2/SDL.h>

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
    Graphics();
    ~Graphics();
    
    SDL_Surface* loadImage(const std::string &filePath);
    
    void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
    
    void flip();
    
    void clear();
    
    SDL_Renderer* getRenderer() const;
    
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif /* GRAPHICS_h */
