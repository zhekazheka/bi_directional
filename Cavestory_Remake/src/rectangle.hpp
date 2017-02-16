//
//  rectangle.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 22/11/2016.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "globals.h"

class Rectangle
{
public:
    Rectangle() { }
    
    Rectangle(int x, int y, int width, int height) :
        _x(x), _y(y), _width(width), _height(height)
    {}
    
    const int getCenterX() const
    {
        return _x + _width / 2;
    }
    
    const int getCenterY() const
    {
        return _y +_height / 2;
    }
    
    const int getLeft() const
    {
        return _x;
    }
    
    const int getRight() const
    {
        return _x + _width;
    }
    
    const int getBottom() const
    {
        return _y + _height;
    }
    
    const int getTop() const
    {
        return _y;
    }
    
    const int getWidth() const
    {
        return _width;
    }
    
    const int getHeight() const
    {
        return _height;
    }
    
    const int getSide(const sides::Side side) const
    {
        return
            side == sides::LEFT ? getLeft() :
            side == sides::RIGHT ? getRight() :
            side == sides::TOP ? getTop() :
            side == sides:: BOTTOM ? getBottom() :
            sides::NONE;
    }
    
    const bool collideWith(const Rectangle &other) const
    {
        return
            getRight() >= other.getLeft() &&
            getLeft() <= other.getRight() &&
            getTop() <= other.getBottom() &&
            getBottom() >= other.getTop();
    }
    
    const bool isValidRectangle() const
    {
        return _x >= 0 && _y >= 0 && _width >= 0 && _height >= 0;
    }
    
    const inline Rectangle getRect() const { return *this; }
    
private:
    int _x, _y, _width, _height;
};

#endif /* rectangle_hpp */
