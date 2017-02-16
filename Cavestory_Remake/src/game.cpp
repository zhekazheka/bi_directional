//
//  Game.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/5/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include <SDL2/SDL.h>

#include "game.hpp"
#include "input.hpp"

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
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
    
    _level = Level("map_1", graphics);
    
    _player = Player(graphics, _level.getPlayerSpawnPoint());
    _hud = HUD(graphics, _player);
    
    
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
        
        if(input.isKeyHeld(SDL_SCANCODE_UP))
        {
            _player.lookUp();
        }
        
        if(input.isKeyHeld(SDL_SCANCODE_DOWN))
        {
            _player.lookDown();
        }
        
        if(input.wasKeyRelease(SDL_SCANCODE_UP))
        {
            _player.stopLookingUp();
        }
        
        if(input.wasKeyRelease(SDL_SCANCODE_DOWN))
        {
            _player.stopLookingDown();
        }
        
        if(input.wasKeyPressed(SDL_SCANCODE_SPACE))
        {
            _player.jump();
        }
        
        if(!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
        {
            _player.stopMoving();
        }
        
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        _graphics = graphics;
        
        draw(graphics);
    }
}

void Game::update(float elapsedTime)
{
    _level.update(elapsedTime);
    _player.update(elapsedTime);
    _hud.update(elapsedTime);
    
    std::vector<Rectangle> others = _level.checkTileCollisions(_player.getBoundingBox());    
    if(others.size() > 0)
    {
        _player.handleTileCollisions(others);
    }
    
    std::vector<Slope> otherSlopes = _level.checkSlopeCollisions(_player.getBoundingBox());
    if(otherSlopes.size() > 0)
    {
        _player.handleSlopeCollisions(otherSlopes);
    }
    
    std::vector<Door> otherDoors = _level.checkDoorCollisions(_player.getBoundingBox());
    if(otherDoors.size() > 0)
    {
        _player.handleDoorCollision(otherDoors, _level, _graphics);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();
    
    _level.draw(graphics);
    _player.draw(graphics);
    
    _hud.draw(graphics);
    
    graphics.flip();
}
