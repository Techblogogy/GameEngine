//
//  TileMap.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/20/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__TileMap__
#define __GameEngine__TileMap__

#include <SDL2/SDL.h>
#include <CoreFoundation/CFBundle.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>

#include "json/json.h"

#include "TextureManager.h"
#include "Camera.h"

struct Tile
{
    SDL_Rect b;
    std::string id;
};

class TileMap
{
public:
    TileMap(std::string tPath/*, SDL_Renderer* r*/); //Tiled Map Constructor
    ~TileMap(); //Tiled Map Deconstuctor
    
    void LoadMap(); //Load Tiled Map
    void LoadResources(); //Load Tiled Map Resources
    
    void RenderStatic(); //Render Static Layers
    void RenderDynamic(); //Render Dynamic Layers
private:
    std::string tiledPath; //Tile Map Path
    
    Json::Value jMap; //JSON Tiled File
    
    SDL_Rect sRect; //Stores rendered texture coords
    SDL_Rect dRect; //Stores texture coords
    
    std::vector<int*> mapLayers;
    std::vector<Tile> tiles;
    
    int tilewidth; //Width of Tile In Pixels
    int tileheight; //Height of tile in pixels
    
    int width; //TileMap width in tiles
    int height; //TileMap height in tiles
};

#endif /* defined(__GameEngine__TileMap__) */
