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
    _currentHealthBar = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 0, 25, 39, 5, 83, 72);
    
    _lvWord = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 81, 81, 11, 7, 38, 55);
    _lvNumber = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 0, 56, 8, 8, 66, 52);
    _expBar = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 0, 72, 40, 8, 83, 52);
    
    _slash = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 72, 48, 8, 8, 100, 36);
    _dashes = Sprite(graphics, "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/sprites/TextBox.png", 81, 51, 15, 11, 132, 26);
}

void HUD::update(float elapsedTime)
{
    _healthNumber1.setSourceRectX(8 * _player.getCurrentHealth());
    
    // calculate width of health bar
    float num = (float)_player.getCurrentHealth() / _player.getMaxHealth();
    _currentHealthBar.setSourceRectW(floor(num * 39)); // 39 width of the bar texture
}

void HUD::draw(Graphics &graphics)
{
    _healthBarSprite.draw(graphics, _healthBarSprite.getX(), _healthBarSprite.getY());
    _healthNumber1.draw(graphics, _healthNumber1.getX(), _healthNumber1.getY());
    _currentHealthBar.draw(graphics, _currentHealthBar.getX(), _currentHealthBar.getY());
    
    _lvWord.draw(graphics, _lvWord.getX(), _lvWord.getY());
    _lvNumber.draw(graphics, _lvNumber.getX(), _lvNumber.getY());
    _expBar.draw(graphics, _expBar.getX(), _expBar.getY());
    
    _slash.draw(graphics, _slash.getX(), _slash.getY());
    _dashes.draw(graphics, _dashes.getX(), _dashes.getY());
}
