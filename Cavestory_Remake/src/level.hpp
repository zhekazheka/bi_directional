//
//  Level.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 11/8/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef level_hpp
#define level_hpp

#include <string>

#include "globals.h"

class Graphics;
struct SDL_Texture;

class Level
{
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    
private:
    std::string _mapName;
    Vector2 _spawnPoint;
    Vector2 _size;
    SDL_Texture *_backgroundTexture;
    
    void loadMap(std::string mapName, Graphics &graphics);
};

#endif /* Level_hpp */
