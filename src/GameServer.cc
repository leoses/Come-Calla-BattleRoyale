#include "GameServer.h"
#include "Message.h"

void GameServer::do_messages(){
    //Abrir conexion servidor
    socket.bind();

    while (true)
    {
        Message* cm;
        Socket *s;

        //Esperamos recibir un mensaje de cualquier socket
        socket.recv(*cm, s);


        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm->getMessageType())
        {
        case MessageType::LOGIN:
        {
            /* code */
            std::cout << "Jugador conectado: " << cm->nick << "\n";
            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients.push_back(std::move(std::make_unique<Socket>(*s)));

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
        case MessageType::PLAYERPOS:
        {
           
            break;
        }
        case MessageType::PLAYERTAM:
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