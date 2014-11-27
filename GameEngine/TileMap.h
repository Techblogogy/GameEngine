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
#include <fstream>
#include <vector>

#include <stdio.h>

#include "json/json.h"

#include "TextureManager.h"
#include "Camera.h"
#include "Vector2.h"
#include "Tile.h"

class TileMap
{
public:
    TileMap(std::string tPath/*, SDL_Renderer* r*/); //Tiled Map Constructor
    ~TileMap(); //Tiled Map Deconstuctor
    
    void LoadMap(); //Load Tiled Map
    void LoadResources(); //Load Tiled Map Resources
    
    void RenderStatic(); //Render Static Layers
    void RenderDynamic(); //Render Dynamic Layers
    
    bool isEmpty(int layerId, Vector2 &pos, Tile &t, float &v);
    
    bool isColL(int layerId, Vector2 &pos, Tile &t, float &v);
    bool isColR(int layerId, Vector2 &pos, Tile &t, float &v);
    bool isColT(int layerId, Vector2 &pos, Tile &t, float &v);
    bool isColB(int layerId, Vector2 &pos, Tile &t, float &v);
    
    void CleanUp();
private:
    std::string tiledPath; //Tile Map Path
    
    Json::Value jMap; //JSON Tiled File
    
    std::vector<int*> mapLayers; //Stores Layers Data
    std::vector<Tile> tiles; //Stores Tilesets Positions
    
    int tilewidth; //Width of Tile In Pixels
    int tileheight; //Height of tile in pixels
    
    int width; //TileMap width in tiles
    int height; //TileMap height in tiles
};

#endif /* defined(__GameEngine__TileMap__) */
