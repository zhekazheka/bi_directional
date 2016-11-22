//
//  Game.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/5/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphics.h"
#include "input.hpp"

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    gameLoop();
}

Game::~Game()
{
    
}

void Game::gameLoop()
{
    Graphics graphics;
    Input input;
    SDL_Event event;
    
    _level = Level("map_1", Vector2(100, 100), graphics);
    
    _player = Player(graphics, _level.getPlayerSpawnPoint());
    
    
    int LAST_UPDATE_TIME = SDL_GetTicks();
    
    // start game loop
    while (true)
    {
        input.beginNewFrame();
        
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.repeat == 0)
                {
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                input.keyUpEvent(event);
            }
            else if(event.type == SDL_QUIT)
            {
                return;
            }
        }
        
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            return;
        }
        else if(input.isKeyHeld(SDL_SCANCODE_LEFT))
        {
            _player.moveLeft();
        }
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT))
        {
            _player.moveRight();
        }
        
        if(!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
        {
            _player.stopMoving();
        }
        
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        draw(graphics);
    }
}

void Game::update(float elapsedTime)
{
    _level.update(elapsedTime);
    _player.update(elapsedTime);
    
    std::vector<Rectangle> others = _level.checkTileCollisions(_player.getBoundingBox());
    
    if(others.size() > 0)
    {
        _player.handleTileCollisions(others);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();
    
    _level.draw(graphics);
    _player.draw(graphics);
    
    graphics.flip();
}
