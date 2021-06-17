#include "Game.h"
#include "Message.h"


void Game::initGame()
{
    std::cout << "Iniciamos el player";
    //Mandamos el mensaje de login, creamos la ventana de SDL etc
    mainPlayer->initPlayer();

    app = SDLApp::GetInstance();
}

Game::Game(const char *s, const char *p, const char *n)
{
    mainPlayer = new Jugador(s, p, n);
    
}

Game::~Game()
{
    //Destruir al jugador
    delete mainPlayer;

    //Destruir tb la ventana de SDL
    delete app;
}

void Game::net_thread()
{
    while (true)
    {
        //Recibir Mensajes de red
        Message em;

        std::cout << "Jugador esperando mensaje\n";
        mainPlayer->getPlayerSocket()->recv(em);

        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        std::cout << "Recibido mensaje de: " << em.getNick() << " de tipo " << (int)em.getMessageType() << "\n";

        switch (em.getMessageType())
        {
        case MessageType::NEWPLAYER:
        {
            PlayerInfo p = em.getPlayerInfo();
            jugadores[em.getNick()] = p;

            std::cout << "El juego del jugador: " << mainPlayer->getNick() << " ha recibido el siguiente PlayerINFO:" << p.tam <<"\n";
            break;
        }

        case MessageType::PICKUPEAT:
        {
            break;
        }
        }
    }
}

void Game::input_thread(){

}

void Game::render()const {

}