//
//  TextureManager.cpp
//  GameEngine
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
    printf("Loading Image. Id: %s, Path: %s \n", name.c_str(), path.c_str());
    
    SDL_Texture* tex;
    
    tempSurface = IMG_Load(path.c_str());
    tex = SDL_CreateTextureFromSurface(GameManager::Instance()->rend , tempSurface);
    
    if (tex == NULL) printf("Image Loading Failed.");
    
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

void TextureManager::Render(std::string name, Vector2 position)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h); //Get Texture Width And Height
    
    bounds.x = 0;
    bounds.y = 0;
    
    destR.x = position.getX() - Camera::Instance()->GetX();
    destR.y = position.getY() - Camera::Instance()->GetY();
    
    destR.w = bounds.w;
    destR.h = bounds.h;
    
    SDL_RenderCopy(GameManager::Instance()->rend, textureMap[name], &bounds, &destR);
}

void TextureManager::Render(std::string name, Vector2 position, int xTile, int yTile, int tileW, int tileH)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    //SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h); //Get Texture Width And Height
    
    bounds.x = xTile * tileW;
    bounds.y = yTile * tileH;
    
    destR.x = position.getX() - Camera::Instance()->GetX();
    destR.y = position.getY() - Camera::Instance()->GetY();
    
    destR.w = bounds.w = tileW; //bounds.w;
    destR.h = bounds.h = tileH; //bounds.h;
    
    SDL_RenderCopy(GameManager::Instance()->rend, textureMap[name], &bounds, &destR);
}

void TextureManager::Render(std::string name,
                            Vector2 position,
                            int xOffL, int width,
                            //int yOffL, int yOffR,
                            int yOff,
                            int tileW, int tileH,
                            int time)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    //SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h); //Get Texture Width And Height
    
    //bounds.x = xTile * tileW;
    
    bounds.y = yOff * tileH;
    bounds.x = ( (SDL_GetTicks()/time % (width) ) + xOffL ) * tileW;
    
   // bounds.x = SDL_GetTicks()/time % width;
    
    //printf("%d\n", (SDL_GetTicks() / time % (bounds.w/tileW))*tileW );
    
    destR.x = position.getX() - Camera::Instance()->GetX();
    destR.y = position.getY() - Camera::Instance()->GetY();
    
    destR.w = bounds.w = tileW; //bounds.w;
    destR.h = bounds.h = tileH; //bounds.h;
    
    SDL_RenderCopy(GameManager::Instance()->rend, textureMap[name], &bounds, &destR);
}

void TextureManager::CleanUp()
{
    printf("Cleaning Texture Manager");
    
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = textureMap.begin(); it!=textureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    textureMap.clear();
    
    delete g_instance;
}