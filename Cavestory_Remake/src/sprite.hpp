//
//  sprite.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/6/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite
{
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
           int width, int height, float posX, float posY);
    
    virtual ~Sprite();
    
    virtual void update();
    virtual void draw(Graphics &graphics, int x, int y);
    
protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    
    float _x, _y;
};

#endif /* sprite_hpp */
