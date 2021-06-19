#pragma once
#include "Socket.h"
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
    bool inGame = false;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Jugador( std::string n);
    ~Jugador();

    std::string getNick(){return nick;}

    SDLTexture* getPlayerTexture();
    Vector2D getPlayerPos();
    int getPlayerTam();
    bool isInGame();

    void setPosition(const Vector2D& newPos);
    void setInGame();
    void setTam(int newTam);
    void setTexture(SDLTexture* newTexture);
    void setNick(std::string newNick);

};