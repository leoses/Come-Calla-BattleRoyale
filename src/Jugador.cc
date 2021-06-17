#include "Jugador.h"
#include "Message.h"
#include "SDLTexture.h"

Jugador::Jugador(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
}

Jugador::~Jugador()
{
}

void Jugador::update()
{
}

void Jugador::login()
{
    //Mandamos el mensaje de LOGIN
    Message logMsg = Message(MessageType::LOGIN, this);
    if (socket.send(logMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

void Jugador::logout()
{
}

void Jugador::initPlayer()
{
    //conectarse al servidor mediante login
    login();
}

Socket* Jugador::getPlayerSocket(){
    return &socket;
    
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
