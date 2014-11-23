//
//  Scene.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/18/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Scene.h"

Scene::Scene()
{
    
}
Scene::~Scene()
{
    
}

void Scene::Add(GameObject*& obj)
{
    objects.push_back(obj);
    obj->Init();
}

void Scene::Update()
{
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->Update();
    }
}

void Scene::Render()
{
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->Render();
    }
}