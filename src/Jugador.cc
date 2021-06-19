#include "Jugador.h"
#include "Message.h"
#include "SDLTexture.h"

Jugador::Jugador(const char *n) : nick(n)
{
}

Jugador::~Jugador()
{
}

void Jugador::setPosition(const Vector2D &newPos)
{
    pos = newPos;
}

void Jugador::setTam(int16_t newTam)
{
    tam = newTam;
}

void Jugador::setTexture(SDLTexture *newTexture)
{
    texture = newTexture;
}

SDLTexture *Jugador::getPlayerTexture()
{
    return texture;
}

Vector2D Jugador::getPlayerPos()
{
    return pos;
}

int16_t Jugador::getPlayerTam()
{
    return tam;
}
