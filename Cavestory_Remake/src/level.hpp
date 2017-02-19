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
#include "rectangle.hpp"
#include "slope.hpp"
#include "animatedtile.hpp"
#include "door.hpp"

class Graphics;
class Enemy;
class Player;
struct SDL_Texture;
struct Tileset;

class Level
{
public:
    Level();
    Level(std::string mapName, Graphics &graphics);
    ~Level();
    
    void update(float elapsedTime, Player &player);
    void draw(Graphics &graphics);
    
    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
    std::vector<Door> checkDoorCollisions(const Rectangle &other);
    
    const Vector2 getPlayerSpawnPoint() const;
    
private:
    std::string _mapName;
    Vector2 _spawnPoint;
    Vector2 _size;
    Vector2 _tileSize;
    
    SDL_Texture *_backgroundTexture;
    
    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    std::vector<Rectangle> _collisionRects;
    std::vector<Slope> _slopes;
    
    std::vector<AnimatedTile> _animatedTileList;
    std::vector<AnimatedTileInfo> _animatedTileInfos;
    
    std::vector<Door> _doorList;
    std::vector<Enemy*> _enemies;
    
    void loadMap(std::string mapName, Graphics &graphics);
    Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
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
