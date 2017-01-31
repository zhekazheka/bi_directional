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
#include "utils.hpp"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

namespace level_constants {
    const std::string LEVEL_SPRITE_SHEET = "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/backgrounds/bkBlue.png";
    
    const std::string MAPS = "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/maps/";
    const std::string TILESETS = "/Users/zhekazheka/Documents/HandMade/Cavestory_Remake/Cavestory_Remake/content/tilesets/";
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
            
            // get all our tile animations for that set
            XMLElement* pTileA = pTileset->FirstChildElement("tile");
            if(pTileA != NULL)
            {
                while (pTileA)
                {
                    AnimatedTileInfo tileInfo;
                    tileInfo.startTileId = pTileA->IntAttribute("id") + firstGid;
                    tileInfo.tilesetFirstGid = firstGid;
                    
                    XMLElement* pAnimation = pTileA->FirstChildElement("animation");
                    if(pAnimation != NULL)
                    {
                        while (pAnimation)
                        {
                            XMLElement* pFrame = pAnimation->FirstChildElement("frame");
                            if(pFrame != NULL)
                            {
                                while (pFrame)
                                {
                                    tileInfo.TileIds.push_back(pFrame->IntAttribute("tileid") + firstGid);
                                    tileInfo.duration = pFrame->IntAttribute("duration");
                                    pFrame = pFrame->NextSiblingElement("frame");
                                }
                            }
                            
                            pAnimation = pAnimation->NextSiblingElement("animation");
                        }
                    }
                    
                    _animatedTileInfos.push_back(tileInfo);
                    pTileA = pTileA->NextSiblingElement("tile");
                }
            }
            
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
                            int closest = 0;
                            if(gid != 0)
                            {
                                for (int i = 0; i < _tilesets.size(); ++i)
                                {
                                    if(_tilesets[i].FirstGid <= gid)
                                    {
                                        if(_tilesets[i].FirstGid >= closest)
                                        {
                                            closest = _tilesets[i].FirstGid;
                                            tls = _tilesets[i];
                                        }
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
                            Vector2 finalTilesetPosition = getTilesetPosition(tls, gid, _tileSize.x, _tileSize.y);
                            
                            bool isAnimatedTile = false;
                            AnimatedTileInfo tileInfo;
                            for (int i = 0; i < _animatedTileInfos.size(); ++i)
                            {
                                if(_animatedTileInfos.at(i).startTileId == gid)
                                {
                                    tileInfo = _animatedTileInfos.at(i);
                                    isAnimatedTile = true;
                                    break;
                                }
                            }
                            
                            if(isAnimatedTile)
                            {
                                std::vector<Vector2> tilesetPositions;
                                for (int i = 0; i < tileInfo.TileIds.size(); ++i)
                                {
                                    tilesetPositions.push_back(getTilesetPosition(tls, tileInfo.TileIds.at(i), _tileSize.x, _tileSize.y));
                                }
                                
                                AnimatedTile animatedTile(tilesetPositions, tileInfo.duration, tls.Texture, _tileSize, finalTilePosition);
                                _animatedTileList.push_back(animatedTile);
                            }
                            else
                            {
                                Tile tile(tls.Texture, Vector2(_tileSize.x, _tileSize.y),
                                          finalTilesetPosition, finalTilePosition);
                                
                                _tileList.push_back(tile);
                            }
                            
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
    
    // parse out the collision
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup != NULL)
    {
        while (pObjectGroup)
        {
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if(ss.str() == "Collisions")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL)
                {
                    while (pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        float width = pObject->FloatAttribute("width");
                        float height = pObject->FloatAttribute("height");
                        _collisionRects.push_back(Rectangle(
                                                        std::ceil(x) * globals::SPRITE_SCALE,
                                                        std::ceil(y) * globals::SPRITE_SCALE,
                                                        std::ceil(width) * globals::SPRITE_SCALE,
                                                        std::ceil(height)  * globals::SPRITE_SCALE)
                                                  );
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            else if(ss.str() == "Slopes")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL)
                {
                    while (pObject)
                    {
                        std::vector<Vector2> points;
                        Vector2 p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));
                        
                        XMLElement* pPolyline = pObject->FirstChildElement("polyline");
                        if(pPolyline != NULL)
                        {
                            std::vector<std::string> pairs;
                            const char* pointString = pPolyline->Attribute("points");
                            
                            std::stringstream ss;
                            ss << pointString;
                            
                            Utils::split(ss.str(), pairs, ' ' );
                            
                            // Now we have each of the pairs
                            for(int i = 0; i < pairs.size(); ++i)
                            {
                                std::vector<std::string> ps;
                                Utils::split(pairs.at(i), ps, ',');
                                
                                points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
                            }
                        }
                        
                        for (int i = 0; i < points.size(); i += 2)
                        {
                            _slopes.push_back(Slope(
                                                    Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
                                                            (p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
                                                    Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
                                                            (p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
                                                    )
                                              );
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            else if(ss.str() == "SpawnPoints")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "player")
                        {
                            _spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y) * globals::SPRITE_SCALE);
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(float elapsedTime)
{
    for (int i = 0; i < _animatedTileList.size(); ++i)
    {
        _animatedTileList.at(i).update(elapsedTime);
    }
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
    
    for (int i = 0; i < _animatedTileList.size(); ++i)
    {
        _animatedTileList.at(i).draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other)
{
    std::vector<Rectangle> others;
    for (int i = 0; i < _collisionRects.size(); ++i)
    {
        if(_collisionRects[i].collideWith(other))
        {
            others.push_back(_collisionRects[i]);
        }
    }
    
    return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other)
{
    std::vector<Slope> others;
    for (int i = 0; i < _slopes.size(); ++i)
    {
        if(_slopes.at(i).collideWith(other))
        {
            others.push_back(_slopes.at(i));
        }
    }
    
    return others;
}

const Vector2 Level::getPlayerSpawnPoint() const
{
    return _spawnPoint;
}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight)
{
    int tilesetWidth, tilesetHeight;
    SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
    int tsxx = gid % (tilesetWidth / _tileSize.x) - 1;
    tsxx *= _tileSize.x;
    
    int tsyy = 0;
    int amount = ((gid-tls.FirstGid) / (tilesetWidth / _tileSize.x));
    tsyy = _tileSize.y * amount;
    return Vector2(tsxx, tsyy);
}
