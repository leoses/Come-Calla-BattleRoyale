#pragma once
class SDLTexture;

#include "Vector2D.h"
#include <SDL2/SDL.h>

class GameObject{
private:
    SDLTexture* textura = nullptr;
    SDL_Rect dimensions;
    Vector2D pos;
    int tam;
    int id;

public:
    GameObject(Vector2D pos_,int id_,int tam_);
    ~GameObject();

    const Vector2D getGameObjectPos() const;
    const int getGameObjectId()const;
    const int getGameObjectTam()const;
    const SDL_Rect& getGameObjectRect()const;

    void setPosition(const Vector2D & newPos);
    void setTam(int newTam);

};
