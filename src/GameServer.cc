#include "GameServer.h"
#include "Message.h"
#include <memory>

void GameServer::do_messages(){

    std::cout << "Bind del gameServer\n";
    if(socket.bind() == -1){
        std::cout << "Bindeo Incorrecto\n";
    }
    else std::cout << "Bindeo Correcto\n";
    
    while (true)
    {
        Message cm;
        Socket* s = nullptr;

        std::cout << "Esperando a recibir mensaje\n";
        //Esperamos recibir un mensaje de cualquier socket
        if(socket.recv(cm, s)==-1){
            std::cout << "Error al recibir el mensaje\n";
        }else std::cout << "HEMOS RECIBIDO UN MENSAJE\n";

        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm.getMessageType())
        {
        case MessageType::LOGIN:
        {
            std::cout << "Mensaje de tipo login\n";

            std::cout << "Jugador conectado: " << cm.getNick() << "\n";
            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            std::cout << "Descriptor del socket:"<<s->sd << "\n";
            clients.push_back(std::move(std::make_unique<Socket>(*s)));
            std::cout << "Antes de asignar el player info nuevo\n";
            players[cm.getNick()]= PlayerInfo();

            //Primero mandarle al player que se acaba de conectar su posicion y su tam

            //socket.send(, s);

            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes menos a si mismo
            std::cout << "Antes de crear el mensaje de newPlayer\n";
            Message newPlayerConnected = Message();
            newPlayerConnected.setMsgType(MessageType::NEWPLAYER);
            newPlayerConnected.setNick(cm.getNick());
            newPlayerConnected.setPlayerInfo(players[cm.getNick()]);
            
            std::cout << "ANtes del for\n";
            int i = 0;
            for (auto it = clients.begin(); it != clients.end(); it++)
			{
                std::cout << "Iteracion n: " << i <<"\n";
                i++;

                std::cout <<"Descripcion del iterador: "<< (**it).sd << "\n";
				if ((**it) !=  (*s))
				{
                    std::cout <<"Tenemos que mandar mensaje\n";
                    //Crear mensaje de jugador nuevo conectado
                    //enviarlo a todos
					socket.send(newPlayerConnected, (**it));

                    std::cout << "Mensaje de nuevo jugador conectado enviado\n";
				}
                std::cout << "Vuelta" << i <<" terminada\n";
			}

            std::cout << "Despues del for\n";

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