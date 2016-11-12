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
    
    const std::string CHARACTER_SPRITE_SHEET = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/MyChar.png";
}

Player::Player()
{
    
}

Player::Player(Graphics &graphics, float x, float y)
        : AnimatedSprite(graphics, player_constants::CHARACTER_SPRITE_SHEET, 0, 0, 16, 16, x, y, 100)
{
    graphics.loadImage(player_constants::CHARACTER_SPRITE_SHEET);
    
    setupAnimations();
    playAnimation("IdleRight");
    
    _facing = RIGHT;
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

void Player::update(float elapsedTime)
{
    _x += _dx * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, _x, _y);
}
