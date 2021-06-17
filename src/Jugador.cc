#include "Jugador.h"
#include "Message.h"
#include "SDLTexture.h"

Jugador::Jugador(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
}

Jugador::~Jugador()
{
    //Borrar textura del jugador
    delete texture;
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

    //inicializar textura
    texture = new SDLTexture();
}

Socket* Jugador::getPlayerSocket(){
    return &socket;
    
}