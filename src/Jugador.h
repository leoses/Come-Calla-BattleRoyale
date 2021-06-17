#pragma once
#include "Socket.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>
class SDLTexture;
 
class Jugador{
private:
    Socket socket;
    std::string nick;
    SDLTexture* texture = nullptr;
    Vector2D pos;
    SDL_Rect dimensions;
    int tam;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Jugador(const char * s, const char * p, const char * n);
    ~Jugador();

    void update();
    void login();
    void logout();
    std::string getNick(){return nick;}
    void initPlayer();

    Socket* getPlayerSocket();


};