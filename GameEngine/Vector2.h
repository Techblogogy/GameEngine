//
//  Vector2.h
//  tst
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __tst__Vector2__
#define __tst__Vector2__

#include <math.h>

class Vector2
{
public:
    Vector2(float xP, float yP); //2D Vector Constructor
    ~Vector2(); //2D Vector Deconstructor
    
    float getX(); //Get Current X Of Vector
    float getY(); //Get Current Y Of Vector
    
    void setX(float xP); //Set X Of 2D Vector
    void setY(float yP); //Set Y of 2D Vector
    
    float getLength(); //Calculate length of vector
    void normalize(); //Normalize vector
private:
    float x,y;
    //int w,h;
};

#endif /* defined(__tst__Vector2__) */
