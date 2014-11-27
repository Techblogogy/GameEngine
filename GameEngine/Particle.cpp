//
//  Particle.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Particle.h"

Particle::Particle(Tile t, Vector2 pos, int l, int d, float s)
{
    texture = t;
    
    position = pos;
    
    life = l;
    angle = d * M_PI / 180;
    
    velocity.x = s * cosf(angle);
    velocity.y = -s * sinf(angle);
}
//Particle::~Particle() {}

void Particle::Update()
{
    
}

void Particle::Render()
{
    
}