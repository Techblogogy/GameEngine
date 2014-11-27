//
//  GameObject.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/17/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "GameObject.h"

GameObject::GameObject(std::string tId, int w, int h)
{
    /* Texture Wibly Wolby */
    
    texture.id = tId; //Set Texture Tile Id
    
    texture.r = 0;
    texture.c = 0;
    
    texture.w = w; //Set Texture Tile Width in pixels
    texture.h = h; //Set Texture Tile Height in pixels
    
    /* Animation Wibly Wobly */
    
    animS.r = 0; //Set Animation Row (Y)
    
    animS.sF = 0; //Set Animation Start Frame
    animS.l = 1; //Set Animation Length
    
    animS.d = 1000/1; //Set Animation Duration
}
GameObject::~GameObject()
{
}

void GameObject::Init()
{
    
}

int velX = 0;
int velY = 0;

void GameObject::Update()
{
    position.x = 100 * sin(SDL_GetTicks() * 1 * M_PI /500) + 100;
    position.y = 100 * cos(SDL_GetTicks() * 1 * M_PI /500) + 100;
    
    //x += 2 * (SDL_GetTicks()/1000;
    
    Camera::Instance()->SetX(100*sin(SDL_GetTicks() * 1 * M_PI /1000)-100);
    
    //float deg = 24;
    
    //velX = sinf(deg*M_PI/180) * 128.0f;
    //velY = cosf(deg*M_PI/180) * 128.0f;
    
    //printf("%f\n", velX);
    //velY = 230.f;
    
    //position.x += velX * (GameManager::Instance()->time.d/1000.0f);
    //position.y += velY * (GameManager::Instance()->time.d/1000.0f);

    //position.x += velX;
    //position.y += velY;
    
    /*if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
    {
        //if (GameManager::Instance()->gScene->tileMap->isColT(1, position, texture, vel))
            position.y -= vel * GameManager::Instance()->time.d;
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
    {
        //if (GameManager::Instance()->gScene->tileMap->isColB(1, position, texture, vel))
            position.y += vel * GameManager::Instance()->time.d;
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
    {
        //if (GameManager::Instance()->gScene->tileMap->isColL(1, position, texture, vel))
            position.x -= vel * GameManager::Instance()->time.d;
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
    {
        //if (GameManager::Instance()->gScene->tileMap->isColR(1, position, texture, vel))
            position.x += vel * GameManager::Instance()->time.d;
    }*/

}

void GameObject::Render()
{
    TextureManager::Instance()->Render(texture, position, animS);
}

void GameObject::CleanUp()
{
    //delete position;
}