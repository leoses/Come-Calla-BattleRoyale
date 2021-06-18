#include "Socket.h"
#include <vector>
#include <map>
#include "PlayerInfo.h"
#include <memory>
#include <mutex>


class GameServer
{
public:
    GameServer(const char * s, const char * p);

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();
    void checkCollisions();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;
    std::map<std::string,PlayerInfo > players;

    /**
     * Socket del servidor
     */
    Socket socket;

};