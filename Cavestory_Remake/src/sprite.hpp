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

#include "globals.h"
#include "rectangle.hpp"

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
    
    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;
    
    void setSourceRectX(int value);
    void setSourceRectY(int value);
    void setSourceRectW(int value);
    void setSourceRectH(int value);
    
    const inline float getX() const
    {
        return _x;
    }
    
    const inline float getY() const
    {
        return _y;
    }
    
protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    
    Rectangle _boundingBox;
    
    float _x, _y;
};

#endif /* sprite_hpp */
