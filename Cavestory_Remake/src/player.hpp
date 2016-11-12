//
//  player.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 10/4/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "animatedsprite.hpp"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite
{
public:
    Player();
    Player(Graphics &graphics, float x, float y);
    
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    
    virtual void setupAnimations();
    virtual void animationDone(std::string currentAnimation);
    
private:
    float _dx, _dy;
    
    Direction _facing;
};

#endif /* player_hpp */
