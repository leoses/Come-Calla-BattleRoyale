#include "Socket.h"
#include <vector>
#include <memory>

class GameServer
{
public:
    GameServer(const char * s, const char * p): socket(s, p)
    {
        std::cout << "Bind del gameServer\n";
        if(socket.bind() == -1){
            std::cout << "Bindeo Incorrecto\n";
        }
        else std::cout << "Bindeo Correcto\n";
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    Socket socket;
};