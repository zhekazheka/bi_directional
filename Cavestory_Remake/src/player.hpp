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
class Door;
class Level;
class Enemy;

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
    void handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics);
    void handleEnemiesCollision(std::vector<Enemy*> &others);
    
    const float getX() const;
    const float getY() const;
    
    const inline int getMaxHealth() const
    {
        return _maxHealth;
    }
    
    const inline int getCurrentHealth() const
    {
        return _currentHealth;
    }
    
    void gainHealth(int amount);
    
private:
    float _dx, _dy;
    
    Direction _facing;
    
    bool _grounded;
    
    bool _lookingUp;
    bool _lookingDown;
    
    int _maxHealth;
    int _currentHealth;
};

#endif /* player_hpp */
