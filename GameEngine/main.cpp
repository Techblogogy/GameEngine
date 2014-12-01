#include <iostream>
#include <SDL2/SDL.h>

#include "GameManager.h"
#include "Particle.h"

void InitGame()
{
    /*Game* gm = new Game(800, 450);
    
    gm->Init();
    gm->Tick();
    gm->CleanUp();*/
    
    //GameManager* gm = new GameManager();
    
    GameManager::Instance()->Init("Game", 800, 450, "tileMap.json");
    
    GameObject* go = new GameObject("spSheet",16,16);
    
    GameManager::Instance()->gScene->Add(go);
    go->position.x = 0;
    go->position.y = 0;
    
    GameManager::Instance()->Tick();
    GameManager::Instance()->Clean();
    
    //delete go;
}

int main(int argc, char * arg[])
{
    InitGame();
    
    return 0;
}