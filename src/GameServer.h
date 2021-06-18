#include "Socket.h"
#include <vector>
#include <map>
#include "ObjectInfo.h"
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
    void createObjects();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::map<std::string,std::unique_ptr<Socket>> clients;
    std::map<std::string,ObjectInfo > players;
    std::map<std::string,ObjectInfo> objects;
    const float TimeTocreate = 2000;
    float initTime = 0;
    int numObjects = 0;
    const int MAXOBJECTS = 20;

    /**
     * Socket del servidor
     */
    Socket socket;

};