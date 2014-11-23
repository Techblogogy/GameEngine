//
//  TextureManager.cpp
//  tst
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "TextureManager.h"

TextureManager* TextureManager::g_instance = NULL;
TextureManager* TextureManager::Instance()
{
    if (!g_instance) {
        g_instance = new TextureManager();
    }
    
    return g_instance;
}

TextureManager::TextureManager()
{
    //rend = g_r;
}

void TextureManager::LoadTexture(std::string path, std::string name)
{
    SDL_Texture* tex;
    
    tempSurface = IMG_Load(path.c_str());
    tex = SDL_CreateTextureFromSurface(GameManager::Instance()->rend , tempSurface);
    
    SDL_FreeSurface(tempSurface);
    
    textureMap[name] = tex;
}

SDL_Texture* TextureManager::GetTexture(std::string name)
{
    return textureMap[name];
}

SDL_Rect TextureManager::GetTextureBounds(std::string name)
{
    SDL_Rect bounds;
    SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h);
    
    bounds.x = 0;
    bounds.y = 0;
    
    return bounds;
}

void TextureManager::RenderTexture(std::string name)
{
}