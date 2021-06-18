#include "GameServer.h"
#include "Message.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <list>

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    //Inicializamos seed para numeros aleatorios
    srand(std::time(0));
    initTime = SDL_GetTicks();
}

void GameServer::do_messages()
{

    std::cout << "Bind del gameServer\n";
    if (socket.bind() == -1)
    {
        std::cout << "Bindeo Incorrecto\n";
    }
    else
        std::cout << "Bindeo Correcto\n";

    while (true)
    {
        Message cm;
        Socket *s = nullptr;

        std::cout << "Esperando a recibir mensaje\n";
        //Esperamos recibir un mensaje de cualquier socket
        if (socket.recv(cm, s) == -1)
        {
            std::cout << "Error al recibir el mensaje\n";
        }

        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm.getMessageType())
        {
        case MessageType::LOGIN:
        {

            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients[cm.getNick()] = std::move(std::make_unique<Socket>(*s));

            //Informacion del jugador
            ObjectInfo n;
            n.tam = rand() % 50;
            n.pos = Vector2D(rand() % (800), rand() % (600));

            //Asignamos
            players[cm.getNick()] = n;

            //Mandarle al player que se acaba de conectar su posicion y su tam
            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes
            Message newPlayerConnected = Message();
            newPlayerConnected.setMsgType(MessageType::NEWPLAYER);
            newPlayerConnected.setNick(cm.getNick());
            newPlayerConnected.setObjectInfo(players[cm.getNick()]);

            //Avisar a todos los jugadores conectados que ha entrado uno nuevo
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                //enviarlo a todos
                socket.send(newPlayerConnected, *((*it).second.get()));
            }

            //Avisar al que ha entrado de donde estan el resto
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                if ((*it).first != cm.getNick())
                {
                    newPlayerConnected.setNick((*it).first);
                    newPlayerConnected.setObjectInfo((*it).second);
                    socket.send(newPlayerConnected, *s);
                }
            }

            for (auto it = objects.begin(); it != objects.end(); ++it)
            {
                newPlayerConnected.setMsgType(MessageType::NEWPICKUP);
                newPlayerConnected.setNick((*it).first);
                newPlayerConnected.setObjectInfo((*it).second);
                socket.send(newPlayerConnected, *s);
            }

            break;
        }
        case MessageType::LOGOUT:
        {
            std::cout << "recivido logout\n";
            /*
            /* code */
            auto it = clients.begin();

            while (it != clients.end() && (*((*it).second.get()) != *s))
                ++it;

            if (it == clients.end())
                std::cout << "El jugador ya se había desconectado previamente\n";
            else
            {
                std::cout << "Jugador desconectado: " << cm.getNick() << "\n";
                clients.erase((*it).first);               //Lo sacamos del vector
                Socket *delSock = (*it).second.release(); //Eliminamos la pertenencia del socket de dicho unique_ptr
                delete delSock;                           //Borramos el socket
            }
            break;
        }
        case MessageType::PLAYERINFO:
        {
            //Actualizamos la posición en la que se encuentra dicho jugador en la memoria del servidor
            players[cm.getNick()] = cm.getObjectInfo();

            //Avisar a todos los jugadores conectados que alguien se ha movido
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (*((*it).second.get()) != *s) //Excepto a la persona que ha enviado el mensaje
                {
                    socket.send(cm, (*((*it).second.get())));
                }
            }

            break;
        }

        case MessageType::PICKUPEAT:
        {
            break;
        }
        default:
            std::cerr << "UNKOWNK MESSAGE RECIEVED\n";
            break;
        }
    }
}

void GameServer::checkCollisions()
{

    std::list<std::map<std::string, ObjectInfo>::iterator> playersToErase;
    std::list<std::map<std::string, ObjectInfo>::iterator> objectsToErase;

    //colision de players con otros players
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        for (auto it2 = it; it2 != players.end(); ++it2)
        {
            SDL_Rect a, b;
            ObjectInfo ap = (*it).second, bp = (*it2).second;
            a = {(int)ap.pos.getX(), (int)ap.pos.getY(), ap.tam, ap.tam};
            b = {(int)bp.pos.getX(), (int)bp.pos.getY(), bp.tam, bp.tam};

            //Si se solapan y el tamaño entre los dos es distinto
            //significa que uno muere
            if (SDL_HasIntersection(&a, &b) && bp.tam != ap.tam)
            {
                if (ap.tam > bp.tam)
                {
                    playersToErase.push_back(it2);
                }
                else
                {
                    playersToErase.push_back(it);
                }
            }
        }
    }
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        for (auto it2 = objects.begin(); it2 != objects.end(); ++it2)
        {
            SDL_Rect a, b;
            ObjectInfo ap = (*it).second, bp = (*it2).second;
            a = {(int)ap.pos.getX(), (int)ap.pos.getY(), ap.tam, ap.tam};
            b = {(int)bp.pos.getX(), (int)bp.pos.getY(), bp.tam, bp.tam};

            //Si se solapan y el tamaño entre los dos es distinto
            //significa que uno muere
            if (SDL_HasIntersection(&a, &b) )
            {
                 std::cout << "colision objeto\n";
                //nos comemos el objeto
                if (bp.tam > ap.tam)
                {
                     std::cout << "objeto comido\n";
                    objectsToErase.push_back(it2);
                    //mandamos el mensaje
                    Message m = Message();
                    m.setMsgType(MessageType::PICKUPEAT);
                    m.setNick((*it2).first);
                    m.setObjectInfo(bp);
                    socket.send(m, *(clients[m.getNick()].get()));
                }
            }
        }
    }

    for (auto player : playersToErase)
    {

        Message cm;
        cm.setMsgType(MessageType::PLAYERDEAD);
        cm.setObjectInfo((*player).second);
        cm.setNick((*player).first);

        //Avisamos a todos los clientes que un jugador va a ser borrado
        for (auto i = clients.begin(); i != clients.end(); ++i)
        {
            socket.send(cm, (*((*i).second.get())));
        }


        players.erase((*player).first);
    }
    for (auto object : objectsToErase)
    {
        std::cout << "objeto destruido\n";
        Message cm;
        cm.setMsgType(MessageType::PICKUPDESTROY);
        cm.setObjectInfo((*object).second);
        cm.setNick((*object).first);
        std::cout << "Creado mensaje de objeto desaparecido\n";
        //Avisamos a todos los clientes que un jugador va a ser borrado
        for (auto i = clients.begin(); i != clients.end(); ++i)
        {
            socket.send(cm, (*((*i).second.get())));
        }
        std::cout << "ENVIADO A TODOS LOS JUGADORES\n";

        objects.erase((*object).first);
    }
}

void GameServer::createObjects()
{
    if (SDL_GetTicks() - initTime > TimeTocreate)
    {
        if (numObjects < MAXOBJECTS)
        {

            //creo el objeto
            ObjectInfo obj;
            obj.tam = 5 + rand() % 25;
            obj.pos = Vector2D(rand() % (800), rand() % (600));
            std::string num = std::to_string(numObjects);
            num.resize(12);
            objects[num] = obj;
            numObjects++;
            //mandar mensaje de objeto nuevo
            Message cm;
            cm.setMsgType(MessageType::NEWPICKUP);
            cm.setObjectInfo((obj));
            cm.setNick((num));
            std::cout << "Creado objeto\n";
            //Avisamos a todos los clientes que un objeto ha sido creado
            for (auto i = clients.begin(); i != clients.end(); ++i)
            {
                socket.send(cm, (*((*i).second.get())));
            }
            std::cout << "ENVIADO OBJETO A TODOS LOS JUGADORES\n";
        }

        initTime = SDL_GetTicks();
    }
}