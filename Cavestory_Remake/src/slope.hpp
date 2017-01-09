//
//  slope.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 27/11/2016.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef slope_hpp
#define slope_hpp

#include "globals.h"
#include "rectangle.hpp"

#import <cmath>

class Slope
{
public:
    Slope() {}
    Slope(Vector2 p1, Vector2 p2) : _p1(p1), _p2(p2)
    {
        if(fabs((float)_p2.x) - fabs((float)_p1.x) != 0)
        {
            _slope = (fabs((float)_p2.y) - fabs((float)_p1.y)) / (fabs((float)_p2.x) - fabs((float)_p1.x));
        }
    }
    
    const bool collideWith(const Rectangle& other) const
    {
        return  (other.getRight() >= _p2.x && other.getLeft() <= _p1.x && other.getTop() <= _p2.y && other.getBottom() >= _p1.y) ||
                (other.getRight() >= _p1.x && other.getLeft() <= _p2.x && other.getTop() <= _p1.y && other.getBottom() >= _p2.y) ||
                (other.getLeft() <= _p1.x && other.getRight() >= _p2.x && other.getTop() <= _p1.y && other.getBottom() >= _p2.y) ||
                (other.getLeft() <= _p2.x && other.getRight() >= _p1.x && other.getTop() <= _p2.y && other.getBottom() >= _p1.y);
    }
    
    const inline float getSlope() const
    {
        return _slope;
    }
    
    const inline Vector2 getP1() const
    {
        return _p1;
    }
    
    const inline Vector2 getP2() const
    {
        return _p2;
    }
    
private:
    Vector2 _p1, _p2;
    float _slope;
};

#endif /* slope_hpp */
