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
class Slope;

class Player : public AnimatedSprite
{
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    void lookUp();
    void stopLookingUp();
    void lookDown();
    void stopLookingDown();
    
    void jump();
    
    virtual void setupAnimations();
    virtual void animationDone(std::string currentAnimation);
    
    void handleTileCollisions(std::vector<Rectangle> &others);
    void handleSlopeCollisions(std::vector<Slope> &others);
    
    const float getX() const;
    const float getY() const;
    
private:
    float _dx, _dy;
    
    Direction _facing;
    
    bool _grounded;
    
    bool _lookingUp;
    bool _lookingDown;
};

#endif /* player_hpp */
