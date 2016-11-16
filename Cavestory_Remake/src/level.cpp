//
//  Level.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 11/8/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "level.hpp"
#include "graphics.h"
#include "tinyxml2.h"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

namespace level_constants {
    const std::string LEVEL_SPRITE_SHEET = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/backgrounds/bkBlue.png";
    
    const std::string MAPS = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/maps/";
    const std::string TILESETS = "/Users/zhekazheka/Development/HandMade/Cavestory_Remake/Cavestory_Remake/content/tilesets/";
}


Level::Level()
{
    
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
            _mapName(mapName),
            _spawnPoint(spawnPoint),
            _size(Vector2(0, 0))
{
    this->loadMap(mapName, graphics);
}

Level::~Level()
{
    
}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
    // TEMPORARY CODE TO LOAD BACKGROUND
//    _backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(level_constants::LEVEL_SPRITE_SHEET));
//    
//    _size = Vector2(1280, 960);
    
    // Parse *.tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss << level_constants::MAPS << mapName << ".tmx";
    
    doc.LoadFile(ss.str().c_str());
    
    XMLElement* mapNode = doc.FirstChildElement("map");
    
    // Get width and height of a map and store it
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    _size = Vector2(width, height);
    
    // Get width and height of a tile and store it
    mapNode->QueryIntAttribute("tilewidth", &width);
    mapNode->QueryIntAttribute("tileheight", &height);
    _tileSize = Vector2(width, height);
    
    // Loading tilesets
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if(pTileset != NULL)
    {
        while (pTileset)
        {
            int firstGid;
//            const char* source = pTileset->FirstChildElement("image")->Attribute("source");
//            char* path;
            std::stringstream ss;
            ss << level_constants::TILESETS << pTileset->Attribute("name") << ".png";
            
            pTileset->QueryIntAttribute("firstgid", &firstGid);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            _tilesets.push_back(Tileset(tex, firstGid));
            
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }
    
    // Loading layers
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if(pLayer != NULL)
    {
        while (pLayer)
        {
            XMLElement* pData = pLayer->FirstChildElement("data");
            if(pData != NULL)
            {
                while (pData)
                {
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if(pTile != NULL)
                    {
                        int tileCounter = 0;
                        while (pTile)
                        {
                            // if gid is 0 nothing should be draw
                            Tileset tls;
                            
                            int gid = pTile->IntAttribute("gid");
                            if(gid != 0)
                            {
                                for (int i = 0; i < _tilesets.size(); ++i)
                                {
                                    if(_tilesets[i].FirstGid <= gid)
                                    {
                                        tls = _tilesets[i];
                                        break;
                                    }
                                }
                                
                                if(tls.FirstGid == -1)
                                {
                                    // No tileset for found for this gid
                                    printf("ERROR: Could't find a tileset for gid: %d", gid);
                                }
                            }
                            
                            // Get the position of the tile in the level
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % _size.x;
                            xx *= _tileSize.x; // tile width
                            
                            yy += _tileSize.y * (tileCounter / _size.x);
                            
                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            // Calculate the position of the tile on the tileset
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            int tsxx = gid % (tilesetWidth / _tileSize.x) - 1;
                            tsxx *= _tileSize.x;
                            
                            int tsyy = 0;
                            int amount = (gid / (tilesetWidth / _tileSize.x));
                            tsyy = _tileSize.y * amount;
                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
                            
                            Tile tile(tls.Texture, Vector2(_tileSize.x, _tileSize.y),
                                      finalTilesetPosition, finalTilePosition);
                            
                            _tileList.push_back(tile);
                            
                            ++tileCounter;
                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    
                    pData = pData->NextSiblingElement("data");
                }
            }
            
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
}

void Level::update(float elapsedTime)
{
    
}

void Level::draw(Graphics &graphics)
{
    // Draw the background
//    SDL_Rect sourceRect = { 0, 0, 64, 64 };
//    SDL_Rect destRect;
//    
//    for (int x = 0; x < _size.x / 64.0f; ++x)
//    {
//        for (int y = 0; y < _size.y / 64.0f; ++y)
//        {
//            destRect.x = x * 64 * globals::SPRITE_SCALE;
//            destRect.y = y * 64 * globals::SPRITE_SCALE;
//            destRect.w = 64 * globals::SPRITE_SCALE;
//            destRect.h = 64 * globals::SPRITE_SCALE;
//            
//            graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
//        }
//    }
    
    for (int i = 0; i < _tileList.size(); ++i)
    {
        _tileList[i].draw(graphics);
    }
}
