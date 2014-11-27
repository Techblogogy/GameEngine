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
    
    delete cBuf;
    
    return jVal;
    
#endif
    
#ifdef _WIN32
    /* Windows Only */
    
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
    
    //dRect.w = tilewidth; //Sets rendering rectange width to width of tile
    //dRect.h = tileheight; //Sets rendering rectange height to height of tile
    
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
        
        tRect.w = tilesets[i]["tilewidth"].asInt(); //Set tilesheet tile width in pixels
        tRect.h = tilesets[i]["tileheight"].asInt(); //Set tilesheet tile height in pixels
        
        tRect.id = tilesets[i]["name"].asString(); //Set tilesheet id
        
        for (int y=0; y<tilesets[i]["imageheight"].asInt()/tRect.h; y++)
        {
            for (int x=0; x<tilesets[i]["imagewidth"].asInt()/tRect.w; x++)
            {
                tRect.r = /*tRect.b.h */ y;
                tRect.c = /*tRect.b.w */ x;
                
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
                
                TextureManager::Instance()->Render(tiles[mapLayers[i][y*height+x]-1], //Tile Struct
                                                   Vector2(x*tilewidth, y*tileheight)); //Render Position
            }
        }
    }
}

void TileMap::RenderDynamic()
{
    
}

/*bool TileMap::isEmpty(int layerId, Vector2 &pos, Tile &t, float &v)
{
    //printf("%d\n", (int)pos.y*height+(int)pos.x);
    
    if (mapLayers[layerId][y*height+x] == 0) return true;
    else return false;
}*/

bool TileMap::isColT(int layerId, Vector2 &pos, Tile &t, float &v)
{
    //Top Edge
    Vector2 p1 = Vector2( (int)(pos.x)/tilewidth, (int)(pos.y-v)/tileheight );
    Vector2 p2 = Vector2( (int)(pos.x+(float)t.w-1.0f)/tilewidth, (int)(pos.y-v)/tileheight );
    
    if (mapLayers[layerId][(int)p1.y*height+(int)p1.x] == 0 &&
        mapLayers[layerId][(int)p2.y*height+(int)p2.x] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TileMap::isColB(int layerId, Vector2 &pos, Tile &t, float &v)
{
    //Bottom Edge
    Vector2 p3 = Vector2( (int)(pos.x)/tilewidth, (int)(pos.y+(float)t.h)/tileheight );
    Vector2 p4 = Vector2( (int)(pos.x+(float)t.w-1.0f)/tilewidth, (int)(pos.y+(float)t.h)/tileheight );
    
    if (mapLayers[layerId][(int)p3.y*height+(int)p3.x] == 0 &&
        mapLayers[layerId][(int)p4.y*height+(int)p4.x] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TileMap::isColL(int layerId, Vector2 &pos, Tile &t, float &v)
{
    //Left Edge
    Vector2 p5 = Vector2( (int)(pos.x-v)/tilewidth, (int)(pos.y)/tileheight );
    Vector2 p6 = Vector2( (int)(pos.x-v)/tilewidth, (int)(pos.y+(float)t.h-1.0f)/tileheight );
    
    if (mapLayers[layerId][(int)p5.y*height+(int)p5.x] == 0 &&
        mapLayers[layerId][(int)p6.y*height+(int)p6.x] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TileMap::isColR(int layerId, Vector2 &pos, Tile &t, float &v)
{
    //Right Edge
    Vector2 p7 = Vector2( (int)(pos.x+(float)t.w)/tilewidth, (int)(pos.y)/tileheight );
    Vector2 p8 = Vector2( (int)(pos.x+(float)t.w)/tilewidth, (int)(pos.y+(float)t.h-1.0f)/tileheight );
    
    if (mapLayers[layerId][(int)p7.y*height+(int)p7.x] == 0 &&
        mapLayers[layerId][(int)p8.y*height+(int)p8.x] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TileMap::CleanUp()
{
    for (std::vector<int*>::size_type i=0; i<mapLayers.size(); i++)
    {
        delete mapLayers[i];
    }
    mapLayers.clear();
    tiles.clear();
}