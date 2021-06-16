#include "GameServer.h"
#include "Message.h"

void GameServer::do_messages(){
    //Abrir conexion servidor
    std::cout << "Comienzo del do messages\n";
    socket.bind();
    std::cout << "Bindeado correcto \n";

    while (true)
    {
        Message cm;
        Socket *s;

        std::cout << "Esperando a recibir mensaje\n";
        //Esperamos recibir un mensaje de cualquier socket
        socket.recv(cm, s);

        std::cout << "HEMOS RECIBIDO UN MENSAJE\n";

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