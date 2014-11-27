//
//  Particle.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__Particle__
#define __GameEngine__Particle__

#include <stdio.h>

#include "Tile.h"
#include "Vector2.h"

class Particle
{
public:
    Particle(Tile t, Vector2 pos, int l, int d, float s);
    ~Particle();
    
    void Update();
    void Render();

private:
    Tile texture;
    
    Vector2 position = Vector2(0,0);
    Vector2 velocity = Vector2(0,0);
    
    int life = 0;
    int angle = 0;
    float speed = 0;
};

#endif /* defined(__GameEngine__Particle__) */
