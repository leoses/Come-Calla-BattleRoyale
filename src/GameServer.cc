#include "GameServer.h"
#include "Message.h"
#include <memory>
#include <ctime>
#include <cstdlib>

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    //Inicializamos seed para numeros aleatorios
    srand(std::time(0));
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
        else
            std::cout << "HEMOS RECIBIDO UN MENSAJE\n";

        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm.getMessageType())
        {
        case MessageType::LOGIN:
        {

            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients.push_back(std::move(std::make_unique<Socket>(*s)));

            //Informacion del jugador
            PlayerInfo n;
            n.tam = 100;
            n.pos = Vector2D(0, 0);

            //Asignamos
            players[cm.getNick()] = n;

            //Mandarle al player que se acaba de conectar su posicion y su tam
            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes
            Message newPlayerConnected = Message();
            newPlayerConnected.setMsgType(MessageType::NEWPLAYER);
            newPlayerConnected.setNick(cm.getNick());
            newPlayerConnected.setPlayerInfo(players[cm.getNick()]);

            //Avisar a todos los jugadores conectados que ha entrado uno nuevo
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                //enviarlo a todos
                socket.send(newPlayerConnected, (**it));
            }

            //Avisar al que ha entrado de donde estan el resto
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                if ((*it).first != cm.getNick())
                {
                    newPlayerConnected.setNick((*it).first);
                    newPlayerConnected.setPlayerInfo((*it).second);
                    socket.send(newPlayerConnected, *s);
                }
            }
            break;
        }
        case MessageType::LOGOUT:
        {
            /*
            /* code */
            //auto it = clients.begin();

            //while (it != clients.end() && (**it !=  *s))
            //    ++it;

            //if (it == clients.end())
            //    std::cout << "El jugador ya se había desconectado previamente\n";
            //else
            //{
            //    std::cout << "Jugador desconectado: " << cm.nick << "\n";
            //    clients.erase(it);                 //Lo sacamos del vector
            //    Socket *delSock = (*it).release(); //Eliminamos la pertenencia del socket de dicho unique_ptr
            //    delete delSock;                    //Borramos el socket
            //}
            break;
        }
        case MessageType::PLAYERINFO:
        {

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