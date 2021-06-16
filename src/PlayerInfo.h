#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>

struct PlayerInfo{
    Vector2D pos;
    int tam;
    SDL_Rect dimensions;
    
    PlayerInfo(){
        pos = Vector2D(0,0);
        int tam = 100;
        dimensions = SDL_Rect({(int)pos.getX(), (int)pos.getY(),tam,tam});
    }

};