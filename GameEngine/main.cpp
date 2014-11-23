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
    GameManager::Instance()->Tick();
    GameManager::Instance()->Clean();
}

int main(int argc, char * arg[])
{
    InitGame();
    
    return 0;
}