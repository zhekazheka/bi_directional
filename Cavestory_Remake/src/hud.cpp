//
//  hud.cpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 02/02/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "hud.hpp"
#include "graphics.h"

HUD::HUD()
{
    
}

HUD::HUD(Graphics& graphics, Player& player)
{
    _player = player;
    _healthBarSprite = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 0, 40, 64, 8, 35, 70);
    _healthNumber1 = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 0, 56, 8, 8, 66, 70);
}

void HUD::update(float elapsedTime)
{
    _healthNumber1.setSourceRectX(8 * _player.getCurrentHealth());
}

void HUD::draw(Graphics &graphics)
{
    _healthBarSprite.draw(graphics, _healthBarSprite.getX(), _healthBarSprite.getY());
    _healthNumber1.draw(graphics, _healthNumber1.getX(), _healthNumber1.getY());
}
