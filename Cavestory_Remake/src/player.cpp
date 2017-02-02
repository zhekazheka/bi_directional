//
//  player.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 10/4/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "player.hpp"
#include "graphics.h"
#include "slope.hpp"

namespace player_constants {
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 0.7f;
    
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    
    const std::string CHARACTER_SPRITE_SHEET = "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/MyChar.png";
}

Player::Player()
{
    
}

Player::Player(Graphics &graphics, Vector2 spawnPoint)
        : AnimatedSprite(graphics, player_constants::CHARACTER_SPRITE_SHEET, 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
        _dx(0),
        _dy(0),
        _facing(RIGHT),
        _grounded(false),
        _lookingUp(false),
        _lookingDown(false),
        _maxHealth(3),
        _currentHealth(3)
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
    addAnimation(1, 3, 0, "IdleLeftUp", 16, 16, Vector2(0, 0));
    addAnimation(1, 3, 16, "IdleRightUp", 16, 16, Vector2(0, 0));
    addAnimation(3, 3, 0, "RunLeftUp", 16, 16, Vector2(0, 0));
    addAnimation(3, 3, 16, "RunRightUp", 16, 16, Vector2(0, 0));
    addAnimation(1, 6, 0, "LookDownLeft", 16, 16, Vector2(0, 0));
    addAnimation(1, 6, 16, "LookDownRight", 16, 16, Vector2(0, 0));
    addAnimation(1, 7, 0, "LookBackLeft", 16, 16, Vector2(0, 0));
    addAnimation(1, 7, 16, "LookBackRight", 16, 16, Vector2(0, 0));
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
    if(_lookingDown && _grounded)
    {
        return;
    }
    _dx = -player_constants::WALK_SPEED;
    
    if(!_lookingUp)
    {
        playAnimation("RunLeft");
    }
    _facing = LEFT;
}

void Player::moveRight()
{
    if(_lookingDown && _grounded)
    {
        return;
    }
    
    _dx = player_constants::WALK_SPEED;
    
    if(!_lookingUp)
    {
        playAnimation("RunRight");
    }
    _facing = RIGHT;
}

void Player::stopMoving()
{
    _dx = 0;
    
    if(!_lookingUp && !_lookingDown)
    {
        playAnimation(_facing == RIGHT ? "IdleRight" : "IdleLeft");
    }
}

void Player::lookUp()
{
    _lookingUp = true;
    if(_dx == 0)
    {
        playAnimation(_facing == RIGHT ? "IdleRightUp" : "IdleLeftUp");
    }
    else
    {
        playAnimation(_facing == RIGHT ? "RunRightUp" : "RunLeftUp");
    }
}

void Player::stopLookingUp()
{
    _lookingUp = false;
}

void Player::lookDown()
{
    _lookingDown = true;
    if(_grounded)
    {
        playAnimation(_facing == RIGHT ? "LookBackRight" : "LookBackLeft");
    }
    else
    {
        playAnimation(_facing == RIGHT ? "LookDownRight" : "LookDownLeft");
    }
}

void Player::stopLookingDown()
{
    _lookingDown = false;
}

void Player::jump()
{
    if(_grounded)
    {
        _dy = 0;
        _dy -= player_constants::JUMP_SPEED;
        _grounded = false;
    }
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
                    _dy = 0;
                    _y = otherRect.getBottom() + 1;
                    if(_grounded)
                    {
                        _dx = 0;
                        _x -= _facing == RIGHT ? 1.0f : -1.0f;
                    }
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

//void handleSlopeCollisions
//Handles collisions with ALL slopes the player is colliding with
void Player::handleSlopeCollisions(std::vector<Slope> &others)
{
    for (int i = 0; i < others.size(); ++i)
    {
        //Calculate where on the slope the player's bottom center is touching
        //and use y=mx+b to figure out the y position to place him at
        //First calculate "b" (slope intercept) using one of the points (b = y - mx)
        Slope slope = others.at(i);
        int b = slope.getP1().y - slope.getSlope() * fabs((float)slope.getP1().x);
        
        //Now get player's center x
        int centerX = _boundingBox.getCenterX();
        
        //Now pass that X into the equation y = mx + b (using our newly found b and x) to get the new y position
        int newY = (slope.getSlope() * centerX) + b - 8; // 8 temp and magic for now
        
        //Re-position the player to the correct "y"
        if(_grounded)
        {
            _y = newY - _boundingBox.getHeight();
            _grounded = true;
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
