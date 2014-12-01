//
//  Particle.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Particle.h"

Particle::Particle(Tile t, Vector2 pos, Vector2 grav, int l, int d, float s)
{
    texture = t;
    
    position = pos;
    
    life = (float)l;
    angle = d * M_PI / 180;
    
    gravityA = grav;
    
    velocity.x = s * cosf(angle);
    velocity.y = s * sinf(angle);
}
Particle::~Particle()
{
    
}

void Particle::Update(float dt)
{
    life -= dt;
    
    if (life > 0)
    {
        position.x += velocity.x * (dt/1000.0f);
        position.y += velocity.y * (dt/1000.0f);
        
        /* Simulate Gravity */
        velocity.y += 9.8f*gravityA.y;
        velocity.x += 9.8f*gravityA.x;
    }
}

void Particle::Render()
{
    TextureManager::Instance()->Render(texture, position);
}