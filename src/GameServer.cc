#include "GameServer.h"
#include "Message.h"

void GameServer::do_messages(){

    std::cout << "Bind del gameServer\n";
    if(socket.bind() == -1){
        std::cout << "Bindeo Incorrecto\n";
    }
    else std::cout << "Bindeo Correcto\n";
    
    while (true)
    {
        Message cm;
        Socket *s;

        //std::cout << "Esperando a recibir mensaje\n";
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
            //LoginMessage* log = static_cast<LoginMessage*>(cm);
            /* code */
            std::cout << "Jugador conectado: " << cm.getNick() << "\n";
            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients.push_back(std::move(std::make_unique<Socket>(*s)));
            players[cm.getNick()]= PlayerInfo();

            //Primero mandarle al player que se acaba de conectar su posicion y su tam

            socket.send(, s);

            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes menos a si mismo
            for (auto it = clients.begin(); it != clients.end(); it++)
			{
				if (**it !=  *s)
				{
                    //Crear mensaje de jugador nuevo conectado
                    //enviarlo a todos
					//socket.send(cm, **it);
				}
			}

            break;

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