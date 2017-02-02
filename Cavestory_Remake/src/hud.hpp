//
//  hud.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 02/02/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef hud_hpp
#define hud_hpp

#include "sprite.hpp"
#include "player.hpp"

class Graphics;

class HUD
{
public:
    HUD();
    HUD(Graphics& graphics, Player& player);
    
    void update(float elapsedTime);
    void draw(Graphics& graphics);
    
private:
    Player _player;
    
    Sprite _healthBarSprite;
    Sprite _healthNumber1;
    
};

#endif /* hud_hpp */
