//
//  Scene.h
//  tst
//
//  Created by Fedor Bobylev on 11/18/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __tst__Scene__
#define __tst__Scene__

#include "GameObject.h"

#include <vector>

class Scene
{
public:
    Scene(); //Scene's Constructor
    ~Scene(); //Scene's Destructor
    
    void Add(GameObject*& obj); //Add Object to scene
    
    void Render(); //Render All Objects to scenes
    void Update(); //Update All Objects on scene
    
    std::vector<GameObject*> objects; //Scene Objects
//private:
    
};

#endif /* defined(__tst__Scene__) */
