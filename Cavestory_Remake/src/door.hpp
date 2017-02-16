//
//  door.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 16/02/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef door_hpp
#define door_hpp

#include "rectangle.hpp"
#include "globals.h"

#include <string>

class Door : public Rectangle
{
public:
    Door() {}
    Door(Rectangle r, std::string dest) :
        Rectangle(r.getLeft() * globals::SPRITE_SCALE,
                  r.getTop() * globals::SPRITE_SCALE,
                  r.getWidth() * globals::SPRITE_SCALE,
                  r.getHeight() * globals::SPRITE_SCALE),
        _destination(dest)
    {}
    
    const inline Rectangle getRectanlge() const { return getRect(); }
    const inline std::string getDestination() const { return _destination; }
    
private:
    std::string _destination;
};

#endif /* door_hpp */
