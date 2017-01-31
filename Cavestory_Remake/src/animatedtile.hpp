//
//  animatedtile.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 31/01/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef animatedtile_hpp
#define animatedtile_hpp

#include <vector>

#include "tile.hpp"
#include "globals.h"

class AnimatedTile : public Tile
{
public:
    AnimatedTile(std::vector<Vector2> tilesetPositions, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position);
    void update(float elapsedTime);
    void draw(Graphics& graphics);
    
protected:
    int _amountOfTime = 0;
    bool _notDone = false;
    
private:
    std::vector<Vector2> _tilesetPositions;
    int _tileToDraw;
    int _duration;
};

struct AnimatedTileInfo
{
public:
    int tilesetFirstGid;
    int startTileId;
    int duration;
    std::vector<int> TileIds;
};

#endif /* animatedtile_hpp */
