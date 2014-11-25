#include <iostream>
#include <SDL2/SDL.h>

#include "GameManager.h"

void InitGame()
{
    /*Game* gm = new Game(800, 450);
    
    gm->Init();
    gm->Tick();
    gm->CleanUp();*/
    
    //GameManager* gm = new GameManager();
    
    GameManager::Instance()->Init("Game", 800, 450);
    
    TextureManager::Instance()->LoadTexture("sp.png", "spSheet");
    
    GameObject* go = new GameObject("spSheet");
    
    GameManager::Instance()->gScene->Add(go);
    go->position.setX(544);
    go->position.setY(32);
    
    GameManager::Instance()->Tick();
    GameManager::Instance()->Clean();
    
    //delete go;
}

int main(int argc, char * arg[])
{
    InitGame();
    
    return 0;
}