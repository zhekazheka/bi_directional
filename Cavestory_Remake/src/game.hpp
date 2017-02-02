//
//  Game.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/5/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "player.hpp"
#include "level.hpp"
#include "hud.hpp"

class Graphics;

class Game
{
public:
    Game();
    ~Game();
    
private:
    void gameLoop();
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    
    Player _player;
    
    Level _level;
    
    HUD _hud;
};

#endif /* Game_hpp */
