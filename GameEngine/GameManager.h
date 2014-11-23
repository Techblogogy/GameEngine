//
//  GameManager.h
//  tst
//
//  Created by Fedor Bobylev on 11/23/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __tst__GameManager__
#define __tst__GameManager__

#include <SDL2/SDL.h> //Main SDL Header
#include <stdio.h> //STD IO Library

#include "TextureManager.h" //Game Texture Manager
#include "Camera.h" //Game Camera
#include "Scene.h" //Game Scene
#include "TileMap.h" //Game Tile Map

class GameManager
{
public:
    static GameManager* Instance(); //GameManager Singleton Instance
    
    SDL_Window* window; //SDL Game Window
    SDL_Renderer* rend; //SDL Game Renderer
    
    Scene* gScene; //Main Game Scene
    TileMap* tMap; //Main Game Tile Map
    
    void Init(std::string wName, int w, int h); //Init Game Manager
    
    void Tick(); //Main Game Loop
    void Clean(); //CleanUp Game Variables
    
private:
    GameManager(); //GameManager Constructor
    static GameManager* g_instance; //Game Manager private instance
    
    bool running = true;
    
    void CreateWindow(std::string name, int w, int h); //Creating SDL Window
    void CreateRenderer(); //Create SDL Renderer
    
    void SetUpCamera(int w, int h); //Setup Camera
    void SetUpTextureManager(); //Setup TextureManager
    void SetUpScene(); //Setup Scene
    
    void Update(); //Handle Game Physics
    void Render(); //Render Game
};

#endif /* defined(__tst__GameManager__) */
