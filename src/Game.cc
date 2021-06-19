#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"
#include "Constants.h"

void Game::initGame()
{
    //Mandamos mensaje de login
    Message logMsg = Message(MessageType::LOGIN, mainPlayer);

    if (socket.send(logMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

Game::Game(const char *s, const char *p, const char *n) : socket(s, p)
{
    app = SDLApp::GetInstance();

    //Creacion de las texturas
    for (auto &image : Resources::imageRoutes)
    {
        app->getTextureManager()->loadFromImg(image.textureId, app->getRenderer(), image.filename);
    }

    mainPlayer = new Jugador(n);
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
    while (isRunning)
    {
        //Recibir Mensajes de red
        Message em;

        socket.recv(em);

        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        std::cout << "Recibido mensaje de: " << em.getNick() << " de tipo " << (int)em.getMessageType() << "\n";

        switch (em.getMessageType())
        {
        case MessageType::NEWPLAYER:
        {
            ObjectInfo p = em.getObjectInfo();
            if (em.getNick() != mainPlayer->getNick())
                jugadores[em.getNick()] = p;
            else
            {
                mainPlayer->setPosition(p.pos);
                mainPlayer->setTam(p.tam);
            }

            break;
        }
        case MessageType::PLAYERINFO:
        {
            ObjectInfo p = em.getObjectInfo();
            jugadores[em.getNick()] = p;
            break;
        }
        case MessageType::PLAYERDEAD:
        {
            //HEMOS MUERTO NOSOTROS
            if (em.getNick() == mainPlayer->getNick())
            {
                //Avisamos al servidor de que hemos muerto para que nos desconecte
                em.setMsgType(MessageType::LOGOUT);
                socket.send(em, socket);
                std::cout << "HAS PERDIDO\n";
                isRunning = false;

            }
            //HA MUERTO OTRO JUGADOR
            else
            {
                std::cout << "Ha muerto un jugador: " << em.getNick() << "\n";
                //Lo quitamos de nuestra lista de jugadores a pintar
                jugadores.erase(em.getNick());
            }
            break;
        }
        case MessageType::PICKUPEAT:
        {
            ObjectInfo p = em.getObjectInfo();
            mainPlayer->setTam(mainPlayer->getPlayerTam() + (p.tam/MIN_SIZE_PICKUP));
            //mandamos un mensaje para actualizar la informacion
            Message cm(MessageType::PLAYERINFO, mainPlayer);
            socket.send(cm, socket);
            break;
        }

        case MessageType::PICKUPDESTROY:
        {

            //Lo quitamos de nuestra lista de objetos a pintar
            objetos.erase(em.getNick());

            break;
        }
        case MessageType::NEWPICKUP:
        {
            ObjectInfo p = em.getObjectInfo();
            objetos[em.getNick()] = p;
            break;
        }
        }
    }

}

void Game::input_thread()
{

    //Updateamos la instancia del input
    HandleEvents::instance()->update();

    Vector2D playerPos = mainPlayer->getPlayerPos();
    bool sendMessage = false;
    //Movemos al jugador localmente
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_W) && playerPos.getY() - PLAYER_SPEEED >= 0)
    {
        mainPlayer->setPosition(Vector2D(playerPos.getX(), playerPos.getY() - PLAYER_SPEEED));
        sendMessage = true;
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_S) && playerPos.getY() + mainPlayer->getPlayerTam() + PLAYER_SPEEED<= WINDOW_HEIGHT)
    {
        mainPlayer->setPosition(Vector2D(playerPos.getX(), playerPos.getY() + PLAYER_SPEEED));
        sendMessage = true;
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_A) && playerPos.getX() - PLAYER_SPEEED >= 0)
    {
        mainPlayer->setPosition(Vector2D(playerPos.getX() - PLAYER_SPEEED, playerPos.getY()));
        sendMessage = true;
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_D) && playerPos.getX() + mainPlayer->getPlayerTam() + PLAYER_SPEEED <= WINDOW_WIDTH)
    {
        mainPlayer->setPosition(Vector2D(playerPos.getX() + PLAYER_SPEEED, playerPos.getY()));
        sendMessage = true;
    }

    if (sendMessage && isRunning)
    {
        Message m(MessageType::PLAYERINFO, mainPlayer);
        socket.send(m, socket);
    }
}

void Game::render() const
{

    //Limpiamos el renderer
    SDL_RenderClear(app->getRenderer());

    //Pintamos el fonfo
    background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);
    
    //Pintamos a los objetos
    SDLTexture* o = app->getTextureManager()->getTexture(Resources::TextureId::Objeto);
    for (auto it = objetos.begin(); it != objetos.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        o->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

    //Pintamos a nuestro jugador
    mainPlayer->getPlayerTexture()->render({(int)mainPlayer->getPlayerPos().getX(),
                                            (int)mainPlayer->getPlayerPos().getY(),
                                            mainPlayer->getPlayerTam(),
                                            mainPlayer->getPlayerTam()});

    //Pintamos a los jugadores contrarios
    SDLTexture *t = app->getTextureManager()->getTexture(Resources::TextureId::Jugador2);
    for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }


    //Volcamos sobre la ventana
    SDL_RenderPresent(app->getRenderer());
}

void Game::run()
{
    while (isRunning)
    {
        input_thread();
        render();
    }
}