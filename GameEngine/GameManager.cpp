//
//  GameManager.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/23/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"

GameManager* GameManager::g_instance = NULL;
GameManager* GameManager::Instance()
{
    if (!g_instance)
    {
        g_instance = new GameManager();
    }
    
    return g_instance;
}

GameManager::GameManager()
{
    
}

/* Initialize GameManager */
void GameManager::Init(std::string wName, int w, int h)
{
    CreateWindow(wName, w, h);
    CreateRenderer();
    
    SetUpCamera(w, h);
    SetUpScene();
    //SetUpTextureManager();
}

void GameManager::CreateWindow(std::string name, int w, int h)
{
    printf("Creating SDL Window. Name: %s, Width: %d, Height: %d \n", name.c_str(), w, h);
    
    window = SDL_CreateWindow(name.c_str(), //Game Window Name
                              SDL_WINDOWPOS_CENTERED, //Game Window Position X
                              SDL_WINDOWPOS_CENTERED, //Game Window Position Y
                              w, //Game Window Width
                              h, //Game Window Height
                              SDL_WINDOW_SHOWN); //Uint32 SDL Window Flags
    
    if (window == NULL)
    {
        printf("Failed To Create Window: %s\n", SDL_GetError());
    }
    else
    {
        printf("Window Creation Succeeded \n");
    }
}

void GameManager::CreateRenderer()
{
    printf("Creating SDL Renderer. \n");
    
    rend = SDL_CreateRenderer(window, //SDL Window
                              -1, //Renderer Id
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Renderer Uint32 Flags
    
    if (rend == NULL)
    {
        printf("Failed To Create Renderer: %s\n", SDL_GetError());
    }
    else
    {
        printf("Renderer Creation Succeeded \n");
    }
}

void GameManager::SetUpCamera(int w, int h)
{
    printf("Setting Camera X: %d, Y: %d, Width: %d, Height: %d \n",0,0,w,h);
    
    Camera::Instance()->SetX(0);
    Camera::Instance()->SetY(0);
    
    Camera::Instance()->SetW(w);
    Camera::Instance()->SetH(h);
}

void GameManager::SetUpScene()
{
    printf("Creating Scene \n");
    
    gScene = new Scene();
    
    tMap = new TileMap("tileMap.json");
    tMap->LoadMap();
    tMap->LoadResources();
    
    if (gScene == NULL)
    {
        printf("Failed To Create Scene \n");
    }
}

void GameManager::SetUpTextureManager()
{
    printf("Creating TextureManager Instance \n");
    
    TextureManager::Instance(); //Init TextureManager Instance
}

/* Game Manager Logic */

void GameManager::Tick()
{
    while (running)
    {
        Update();
        Render();
    }
}

void GameManager::Update()
{
    /* Get SDL Event */
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                running = false;
            break;
                
            default:
            break;
        }
    }
    
    /* Main Logic */
    gScene->Update();
}

void GameManager::Render()
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 1);
    
    SDL_RenderClear(rend);
    
    tMap->RenderStatic();
    gScene->Render();
    
    SDL_RenderPresent(rend);
}

/* Clean Up Game Manager */

void GameManager::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    
    SDL_Quit(); //Quit SDL
}