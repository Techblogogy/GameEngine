//
//  GameObject.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/17/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__GameObject__
#define __GameEngine__GameObject__

//#include <SDL2/SDL.h> //Include SDL2
#include <string> //Inlcude STD String
#include <math.h>

//#include "GameManager.h"
#include "Vector2.h" //Include Vector 2d library
#include "Camera.h" //Camera Class
#include "TextureManager.h" //Include texture manager

class GameObject
{
public:
    GameObject(std::string tId); //GameObjet Constructor
    ~GameObject(); //GameObject Destructor
    
    virtual void Init(); //GameObject Initiation
    virtual void Render(); //GameObject Render
    virtual void Update(); //GameObject Update
    
    Vector2 position = Vector2(0,0);; //Stores GameObjects Position
    
    int GetW() { return objRect.w; }; //Get Gameobjects Width
    int GetH() { return objRect.h; }; //Get GameObject Height
    
    void CleanUp();
private:
    //SDL_Renderer* gRenderer; //SDL Game Renderer
    
    std::string textureId; //Texture id
    
    SDL_Rect texRect; //Stores Texture X Y Width And Height
    SDL_Rect objRect; //Stores Game Object X Y Width And Height
};

#endif /* defined(__GameEngine__GameObject__) */
