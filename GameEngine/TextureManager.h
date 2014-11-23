//
//  TextureManager.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__TextureManager__
#define __GameEngine__TextureManager__

//#include "GameManager.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <string>
#include <map>

class TextureManager
{
public:
    static TextureManager* Instance(/*SDL_Renderer* rend*/); //Get or create instance of TextureManager
    
    void LoadTexture(std::string path, std::string name); //Load Texture From File
    SDL_Texture* GetTexture(std::string name); //Get Texture from file
    SDL_Rect GetTextureBounds(std::string name); //Get Texture bounds
    void RenderTexture(std::string name); //Render Texture
    
    //void CleanUp(); //Destroys SDL Textures
private:
    TextureManager(/*SDL_Renderer* g_R*/); //Private texture constructor
    static TextureManager* g_instance; //Texture Manager Instance
    
    std::map<std::string, SDL_Texture*> textureMap; //Stores Game Textures
    
    SDL_Surface* tempSurface; //Temporary surface for texture creation
    //SDL_Renderer* rend; //SDL Game renderer
};

#endif /* defined(__GameEngine__TextureManager__) */
