//
//  enemy.cpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 19/02/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "enemy.hpp"

Enemy::Enemy() {}

Enemy::Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate)
    : AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate),
    _direction(LEFT),
    _maxHealth(0),
    _currentHealth(0)
{}

void Enemy::update(int elapsedTime, Player &player)
{
    AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, _x, _y);
}


Bat::Bat() {}

Bat::Bat(Graphics &graphics, Vector2 spawnPoint)
    : Enemy(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/NpcCemet.png", 32, 32, 16, 16, spawnPoint, 140)
{
    setupAnimations();
    playAnimation("FlyLeft");
}

void Bat::update(int elapsedTime, Player &player)
{
    _direction = player.getX() > _x ? RIGHT : LEFT;
    playAnimation(_direction == RIGHT ? "FlyRight" : "FlyLeft");
    
    Enemy::update(elapsedTime, player);
}

void Bat::draw(Graphics &graphics)
{
    Enemy::draw(graphics);
}

void Bat::setupAnimations()
{
    addAnimation(3, 2, 32, "FlyLeft", 16, 16, Vector2(0, 0));
    addAnimation(3, 2, 48, "FlyRight", 16, 16, Vector2(0, 0));
}

void Bat::animationDone(std::string currentAnimation)
{
    
}
