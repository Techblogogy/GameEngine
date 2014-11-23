//
//  TileMap.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/20/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "TileMap.h"

TileMap::TileMap(std::string tP)
{
    tiledPath = tP;
}

TileMap::~TileMap()
{
    
}

Json::Value ReadJSONFile(std::string path)
{
#ifdef __APPLE__&&__MACH__
    
    /* MAC ONLY */
    /* Get Current Mac Application Directory */
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (!mainBundle) printf("Failed To Get Main Application Bundle \n");
    
    char* cBuf = new char[200];
    
    CFURLRef resourceUrl = CFBundleCopyResourceURL(mainBundle, CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingASCII), NULL, NULL);
    if (!resourceUrl) printf("Failed To Get Resource Folder Path \n");
    CFURLGetFileSystemRepresentation(resourceUrl, true, (Uint8*)cBuf, 200);
    
    /* Read Tile Map File */
    Json::Value jVal;
    Json::Reader jTxt; //JSON File Parser
    std::ifstream fStr(cBuf, std::ifstream::binary);
    bool loaded = jTxt.parse(fStr, jVal, false);
    if (!loaded) printf("Failed To Load Tiled Map File. Path: %s Reason: %s \n", cBuf, jTxt.getFormatedErrorMessages().c_str());
    
    return jVal;
    
#endif
    
#ifdef _WIN32
    /* Read Tile Map File */
    Json::Value jVal;
    Json::Reader jTxt; //JSON File Parser
    std::ifstream fStr(path, std::ifstream::binary);
    bool loaded = jTxt.parse(fStr, jVal, false);
    if (!loaded) printf("Failed To Load Tiled Map File. Path: %s Reason: %s \n", path.c_str(), jTxt.getFormatedErrorMessages().c_str());
    
    return jVal;
#endif
}

void TileMap::LoadMap()
{
    printf("Loading Tiled Map File At: %s \n", tiledPath.c_str());
    
    jMap = ReadJSONFile(tiledPath);
    
    /* Init Variables */
    
    tilewidth = jMap["tilewidth"].asInt(); //Defines Width of Tile in pixels
    tileheight = jMap["tileheight"].asInt(); //Defines Height of Tile in pixels
    
    width = jMap["width"].asInt(); //Defines Width Of Tilemap in tiles
    height = jMap["height"].asInt(); //Defines Width Of Tilemap in tiles
    
    dRect.w = tilewidth; //Sets rendering rectange width to width of tile
    dRect.h = tileheight; //Sets rendering rectange height to height of tile
    
    const Json::Value jLayers = jMap["layers"]; //Get's all tile map layers
    for (int i=0; i<jLayers.size(); i++) //Loops thorught each tile map layer
    {
        mapLayers.push_back(new int[width*height]); //Adds layer map to Layers List
        
        const Json::Value jLayer = jLayers[i]["data"]; //Get's layer data
        for (int a=0; a<jLayer.size(); a++) //Loop to copy data from json layer to array of integers
        {
            mapLayers[i][a] = jLayer[a].asInt();
        }
    }
}

void TileMap::LoadResources()
{
    Tile tRect; //Tile Rectangle
    const Json::Value tilesets = jMap["tilesets"]; //Get list of JSON tilesheets
    
    for (int i=0; i<tilesets.size(); i++) //Loop thought JSON tilesheets
    {
        TextureManager::Instance()->LoadTexture(tilesets[i]["image"].asString(),
                                                tilesets[i]["name"].asString()); //Load tilesheet texture using bitmap
        
        tRect.b.w = tilesets[i]["tilewidth"].asInt(); //Set tilesheet tile width in pixels
        tRect.b.h = tilesets[i]["tileheight"].asInt(); //Set tilesheet tile height in pixels
        
        tRect.id = tilesets[i]["name"].asString(); //Set tilesheet id
        
        for (int y=0; y<tilesets[i]["imageheight"].asInt()/tRect.b.h; y++)
        {
            for (int x=0; x<tilesets[i]["imagewidth"].asInt()/tRect.b.w; x++)
            {
                tRect.b.y = tRect.b.h * y;
                tRect.b.x = tRect.b.w * x;
                
                tiles.push_back(tRect);
            }
        }
    }
}

void TileMap::RenderStatic()
{
    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            for (int i=0; i<mapLayers.size(); i++)
            {
                if (mapLayers[i][y*height+x] == 0) continue;
                
                sRect = tiles[mapLayers[i][y*height+x]-1].b;
                
                dRect.x = x*tilewidth - Camera::Instance()->GetX();
                dRect.y = y*tileheight - Camera::Instance()->GetY();
                
                SDL_RenderCopy(GameManager::Instance()->rend,
                               TextureManager::Instance(/*rend*/)->GetTexture(tiles[mapLayers[i][y*height+x]-1].id),
                               &sRect,
                               &dRect);
            }
        }
    }
}

void TileMap::RenderDynamic()
{
    
}