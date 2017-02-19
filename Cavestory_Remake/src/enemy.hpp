//
//  enemy.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 19/02/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include "animatedsprite.hpp"
#include "player.hpp"

class Enemy : public AnimatedSprite
{
public:
    Enemy();
    Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);
    
    virtual void update(int elapsedTime, Player &player);
    virtual void draw(Graphics &graphics);
    
    const inline int getMaxHealth() const { return _maxHealth; }
    const inline int getCurrentHealth() const { return _currentHealth; }
    
protected:
    Direction _direction;
    
    int _maxHealth;
    int _currentHealth;
};


class Bat : public Enemy
{
public:
    Bat();
    Bat(Graphics &graphics, Vector2 spawnPoint);
    
    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
    
    void setupAnimations();
    void animationDone(std::string currentAnimation);
    
private:
    
};

#endif /* enemy_hpp */
