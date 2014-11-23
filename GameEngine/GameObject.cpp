//
//  GameObject.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/17/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "GameObject.h"

GameObject::GameObject(std::string tId)
{
    textureId = tId;
    
    texRect = TextureManager::Instance()->GetTextureBounds(textureId);
    
    position = new Vector2(0,0);
    
    objRect.w = texRect.w;
    objRect.h = texRect.h;
}
GameObject::~GameObject()
{
}

void GameObject::Init()
{
    
}
//int x = 0;
void GameObject::Update()
{
    //position->setX(100 * sin(SDL_GetTicks() * 1 * M_PI /500) + 100);
    //position->setY(100 * cos(SDL_GetTicks() * 1 * M_PI /500) + 100);
    
    //x += 2 * (SDL_GetTicks()/1000;
    
    //Camera::Instance()->SetX(100*sin(SDL_GetTicks() * 1 * M_PI /5000)-100);
}

void GameObject::Render()
{
    objRect.x = position->getX() - Camera::Instance()->GetX();
    objRect.y = position->getY() - Camera::Instance()->GetY();
    
    SDL_RenderCopy(GameManager::Instance()->rend,
                   TextureManager::Instance()->GetTexture(textureId),
                   &texRect,
                   &objRect);
}

void GameObject::CleanUp()
{
    delete position;
}