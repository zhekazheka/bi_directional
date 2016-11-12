//
//  globals.h
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/6/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef globals_h
#define globals_h

namespace globals
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HIGHT = 480;
    
    const float SPRITE_SCALE = 2.0f;
}

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Vector2
{
    int x, y;
    
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
    
    Vector2 zero()
    {
        return Vector2(0, 0);
    }
};

#endif /* globals_h */
