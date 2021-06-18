#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"

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
    std::cout << "Destructora de Game\n";
    //Destruir al jugador
    delete mainPlayer;

    //Destruir tb la ventana de SDL
    //app->destroyWindow();
    delete app;
}

void Game::net_thread()
{
    while (isRunning)
    {
        //Recibir Mensajes de red
        Message em;

        mainPlayer->getPlayerSocket()->recv(em);

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
            if(em.getNick() == mainPlayer->getNick()){
                //Avisamos al servidor de que hemos muerto para que nos desconecte
                Socket* socket = mainPlayer->getPlayerSocket();
                em.setMsgType(MessageType::LOGOUT);
                socket->send(em, *socket);
                std::cout << "HAS PERDIDO\n";
                isRunning = false;

               // jugadores.erase(em.getNick());
                std::cout << "He muerto\n";
            }
            //HA MUERTO OTRO JUGADOR
            else{
                std::cout << "Ha muerto un jugador: " << em.getNick() << "\n";
                //Lo quitamos de nuestra lista de jugadores a pintar
                jugadores.erase(em.getNick());
            }
            break;
            
        }
        case MessageType::PICKUPEAT:
        {
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

    std::cout << "Salimos del thread de escucha\n";
    return;
}

void Game::input_thread()
{
      std::cout << "entrada input_thread\n";
    //Updateamos la instancia del input
    HandleEvents::instance()->update();

    Vector2D playerPos = mainPlayer->getPlayerPos();
    Socket* socket = mainPlayer->getPlayerSocket();
    bool sendMessage = false;
    //Movemos al jugador localmente
    if(HandleEvents::instance()->isKeyDown(SDL_SCANCODE_W)){
        mainPlayer->setPosition(Vector2D(playerPos.getX(), playerPos.getY()-2));
        sendMessage = true;
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_S)){
        mainPlayer->setPosition(Vector2D(playerPos.getX(), playerPos.getY()+2));
        sendMessage = true;  
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_A)){
        mainPlayer->setPosition(Vector2D(playerPos.getX()-2, playerPos.getY()));
        sendMessage = true;
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_D)){
        mainPlayer->setPosition(Vector2D(playerPos.getX()+2, playerPos.getY()));
        sendMessage = true;
    }

    if(sendMessage && isRunning){
        Message m(MessageType::PLAYERINFO, mainPlayer);
        socket->send(m, *socket);
    }
        std::cout << "salida input_thread\n";
}

void Game::render() const
{
     std::cout << "entrada render\n";
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
        ObjectInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

     //Pintamos a los objetos
    t = app->getTextureManager()->getTexture(Resources::TextureId::Objeto);
    for (auto it = objetos.begin(); it != objetos.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

    //Volcamos sobre la ventana
    SDL_RenderPresent(app->getRenderer());
    std::cout << "salida render\n";
}

void Game::run(){
    while(isRunning){
        input_thread();
        render();
    }
}