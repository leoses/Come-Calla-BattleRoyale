#include "Socket.h"
#include <vector>
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <memory>
#include <map>

struct PlayerInfo{
Vector2D pos;
int tam;
SDL_Rect dimensions;
PlayerInfo(){
    pos = Vector2D(0,0);
    int tam = 100;
    dimensions = SDL_Rect({pos.getX(), pos.getY(),tam,tam});
}


};
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
    std::map<std::string,PlayerInfo > players;

    /**
     * Socket del servidor
     */
    Socket socket;
};