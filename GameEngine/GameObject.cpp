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
    
    texture.r = 0; //
    texture.c = 0; //
    
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

float dir = 35;
Vector2 vel = Vector2(0,0);

void GameObject::Update(float dt)
{
    /*if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
    {
        if (GameManager::Instance()->gScene->tileMap->isColT(1, position, texture, vel))
            
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
    {
        if (GameManager::Instance()->gScene->tileMap->isColB(1, position, texture, vel))
            position.y += velY * (dt/1000.0f);
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
    {
        if (GameManager::Instance()->gScene->tileMap->isColL(1, position, texture, vel))
            position.x -= velX * (dt/1000.0f);
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
    {
        if (GameManager::Instance()->gScene->tileMap->isColR(1, position, texture, vel))
            position.x += velX * (dt/1000.0f);
    }*/
    
    vel.x = 150 * cosf(dir*M_PI/180);
    vel.y = 150 * sinf(dir*M_PI/180);
    
    Vector2 fP = Vector2(position.x + vel.x * (dt/1000.0f),
                         position.y);
    
    if (GameManager::Instance()->gScene->tileMap->isEmpty(1, fP, texture, fP))
    {
        position.x += vel.x * (dt/1000.0f);
        //position.y += vel.y * (dt/1000.0f);
    }
    
    fP = Vector2(position.x,
                 position.y + vel.y * (dt/1000.0f));
    
    if (GameManager::Instance()->gScene->tileMap->isEmpty(1, fP, texture, fP))
    {
        //position.x += vel.x * (dt/1000.0f);
        position.y += vel.y * (dt/1000.0f);
    }
}

void GameObject::Render()
{
    TextureManager::Instance()->Render(texture, position, animS);
}

void GameObject::CleanUp()
{
    //delete position;
}