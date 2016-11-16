//
//  tile.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 16/11/2016.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

#include "globals.h"

struct SDL_Texture;
class Graphics;

class Tile
{
public:
    Tile();
    Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
    
    void update(int elapsedTime);
    void draw(Graphics &graphics);
    
private:
    SDL_Texture* _tileset;
    Vector2 _size;
    Vector2 _tilesetPosition; // where on tileset tile is
    Vector2 _position; // where on a map tile is
};

#endif /* tile_hpp */
