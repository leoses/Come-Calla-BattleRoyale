#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    GameServer es(argv[1], argv[2]);
    std::cout << "Creacion del game server completada\n";

    std::thread net_thread([&es]() { es.do_messages(); });
    
    while (true)
    {
        es.checkCollisions();
    }
    return 0;
}
