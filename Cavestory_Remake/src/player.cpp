//
//  player.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 10/4/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "player.hpp"
#include "graphics.h"

namespace player_constants {
    const float WALK_SPEED = 0.2f;
    
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    
    const std::string CHARACTER_SPRITE_SHEET = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/MyChar.png";
}

Player::Player()
{
    
}

Player::Player(Graphics &graphics, Vector2 spawnPoint)
        : AnimatedSprite(graphics, player_constants::CHARACTER_SPRITE_SHEET, 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
        _dx(0),
        _dy(0),
        _facing(RIGHT),
        _grounded(false)
{
    graphics.loadImage(player_constants::CHARACTER_SPRITE_SHEET);
    
    setupAnimations();
    playAnimation("IdleRight");
}

void Player::setupAnimations()
{
    addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
    addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation)
{
    
}

const float Player::getX() const
{
    return _x;
}

const float Player::getY() const
{
    return _y;
}

void Player::moveLeft()
{
    _dx = -player_constants::WALK_SPEED;
    playAnimation("RunLeft");
    _facing = LEFT;
}

void Player::moveRight()
{
    _dx = player_constants::WALK_SPEED;
    playAnimation("RunRight");
    _facing = RIGHT;
}

void Player::stopMoving()
{
    _dx = 0;
    playAnimation(_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
    // Figure out what side is player collision on and move to accordingly
    for (int i = 0; i < others.size(); ++i)
    {
        Rectangle otherRect = others[i];
        sides::Side collisionSide = Sprite::getCollisionSide(otherRect);
        if(collisionSide != sides::NONE)
        {
            switch (collisionSide) {
                case sides::TOP:
                    _y = otherRect.getBottom() + 1;
                    _dy = 0;
                    break;
                    
                case sides::BOTTOM:
                    _y = otherRect.getTop() - getBoundingBox().getHeight() - 1;
                    _dy = 0;
                    _grounded = true;
                    break;
                    
                case sides::LEFT:
                    _x = otherRect.getRight() + 1;
                    break;
                    
                case sides::RIGHT:
                    _x = otherRect.getLeft() - getBoundingBox().getWidth() - 1;
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Player::update(float elapsedTime)
{
    // Apply gravity
    if(_dy <= player_constants::GRAVITY_CAP)
    {
        _dy += player_constants::GRAVITY * elapsedTime;
    }
    
    // Move by dx
    _x += _dx * elapsedTime;
    
    // Move by dy
    _y += _dy * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, _x, _y);
}
