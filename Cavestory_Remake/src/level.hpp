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
#include <vector>

#include "globals.h"
#include "tile.hpp"

class Graphics;
struct SDL_Texture;
struct Tileset;

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
    Vector2 _tileSize;
    
    SDL_Texture *_backgroundTexture;
    
    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    
    void loadMap(std::string mapName, Graphics &graphics);
};

struct Tileset
{
    SDL_Texture* Texture;
    int FirstGid;
    
    Tileset()
    {
        FirstGid = -1;
    }
    
    Tileset(SDL_Texture* texture, int firstGid)
    {
        Texture = texture;
        FirstGid = firstGid;
    }
};

#endif /* Level_hpp */
