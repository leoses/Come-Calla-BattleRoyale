#include "Game.h"
#include "Message.h"
#include "Resources.h"

void Game::initGame()
{
    //Mandamos el mensaje de login, creamos la ventana de SDL etc
    mainPlayer->initPlayer();
}

Game::Game(const char *s, const char *p, const char *n)
{
    app = SDLApp::GetInstance();

    //Creacion de las texturas
    for (auto &image : Resources::imageRoutes)
    {
        app->getTextureManager()->loadFromImg(image.textureId, app->getRenderer(), image.filename);
    }

    mainPlayer = new Jugador(s, p, n);
    mainPlayer->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Jugador1));

    background = app->getTextureManager()->getTexture(Resources::TextureId::Escenario);
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
            if (em.getNick() != mainPlayer->getNick())
                jugadores[em.getNick()] = p;
            else
            {
                mainPlayer->setPosition(p.pos);
                mainPlayer->setTam(p.tam);
            }

            std::cout << "El juego del jugador: " << mainPlayer->getNick() << " ha recibido el siguiente PlayerINFO:" << p.tam << "\n";
            break;
        }

        case MessageType::PICKUPEAT:
        {
            break;
        }
        }
    }
}

void Game::input_thread()
{
}

void Game::render() const
{
    //Limpiamos el renderer
    SDL_RenderClear(app->getRenderer());
    
    //Pintamos el fonfo
    background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);

    //Pintamos a nuestro jugador
    mainPlayer->getPlayerTexture()->render({(int)mainPlayer->getPlayerPos().getX(),
                                            (int)mainPlayer->getPlayerPos().getY(),
                                            mainPlayer->getPlayerTam(),
                                            mainPlayer->getPlayerTam()});

    //Pintamos a los jugadores contrarios
    SDLTexture *t = app->getTextureManager()->getTexture(Resources::TextureId::Jugador2);
    for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        PlayerInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

    //Volcamos sobre la ventana
    SDL_RenderPresent(app->getRenderer());
}