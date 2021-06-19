#include "Jugador.h"
#include "Message.h"
#include "SDLTexture.h"

Jugador::Jugador(std::string n) :  nick(n)
{
}

Jugador::~Jugador()
{
    
}

void Jugador::setPosition(const Vector2D& newPos){
    pos = newPos;
}

void Jugador::setTam(int newTam){
    tam = newTam;
}

void Jugador::setTexture(SDLTexture* newTexture){
    texture =newTexture;
}

SDLTexture* Jugador::getPlayerTexture(){
    return texture;
}

Vector2D Jugador::getPlayerPos(){
    return pos;
}

int Jugador::getPlayerTam(){
    return tam;
}

bool Jugador::isInGame(){
    return inGame;
}

void Jugador::setInGame(){
    inGame = true;
}

void Jugador::setNick(std::string newNick){
    nick = newNick;
}
