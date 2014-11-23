//
//  TileMap.cpp
//  tst
//
//  Created by Fedor Bobylev on 11/20/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "TileMap.h"

#include <CoreFoundation/CFBundle.h>

TileMap::TileMap(std::string tP/*, SDL_Renderer* r*/)
{
    tiledPath = tP;
    //rend = r;
}

TileMap::~TileMap()
{
    
}

void TileMap::LoadMap()
{
    /* MAC ONLY */
    /* Get Current Mac Application Directory */
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (!mainBundle) std::cout << "Failed" << std::endl;
    
    char* cBuf = new char[200];
    
    CFURLRef resourceUrl = CFBundleCopyResourceURL(mainBundle, CFStringCreateWithCString(NULL, "tileMap.json", kCFStringEncodingASCII), NULL, NULL);
    CFURLGetFileSystemRepresentation(resourceUrl, true, (Uint8*)cBuf, 200);
    
    std::cout << cBuf << std::endl;
    
    /* Read Tile Map File */
    Json::Reader jTxt; //JSON File Parser
    std::ifstream fStr(cBuf, std::ifstream::binary);
    bool loaded = jTxt.parse(fStr, jMap, false);
    if (!loaded) std::cout << jTxt.getFormatedErrorMessages() << std::endl;
    
    /* Init Variables */
    
    tilewidth = jMap["tilewidth"].asInt();
    tileheight = jMap["tileheight"].asInt();
    
    width = jMap["width"].asInt();
    height = jMap["height"].asInt();
    
    dRect.w = tilewidth;
    dRect.h = tileheight;
    
    const Json::Value jLayers = jMap["layers"];
    for (int i=0; i<jLayers.size(); i++)
    {
        mapLayers.push_back(new int[width*height]);
        
        const Json::Value jLayer = jLayers[i]["data"];
        for (int a=0; a<jLayer.size(); a++)
        {
            mapLayers[i][a] = jLayer[a].asInt();
        }
    }
}

void TileMap::LoadResources()
{
    Tile tRect;
    const Json::Value tilesets = jMap["tilesets"];
    
    for (int i=0; i<tilesets.size(); i++)
    {
        TextureManager::Instance(/*rend*/)->LoadTexture(tilesets[i]["image"].asString(), tilesets[i]["name"].asString());
        
        tRect.b.w = tilesets[i]["tilewidth"].asInt();
        tRect.b.h = tilesets[i]["tileheight"].asInt();
        
        tRect.id = tilesets[i]["name"].asString();
        
        for (int y=0; y<tilesets[i]["imageheight"].asInt()/tRect.b.h; y++)
        {
            for (int x=0; x<tilesets[i]["imagewidth"].asInt()/tRect.b.w; x++)
            {
                tRect.b.y = tRect.b.h * y;
                tRect.b.x = tRect.b.w * x;
                
                std::cout << tRect.b.x << std::endl;
                
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