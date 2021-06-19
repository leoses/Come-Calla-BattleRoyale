#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <string>
class SDLTexture;
 
class Jugador{
private:

    std::string nick;
    SDLTexture* texture = nullptr;
    Vector2D pos;
    int tam;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Jugador(const char * n);
    ~Jugador();

    std::string getNick(){return nick;}

    SDLTexture* getPlayerTexture();
    Vector2D getPlayerPos();
    int getPlayerTam();

    void setPosition(const Vector2D& newPos);
    void setTam(int newTam);
    void setTexture(SDLTexture* newTexture);

};