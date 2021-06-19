#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    GameServer es(argv[1], argv[2]);

    std::thread net_thread([&es]() { es.do_messages(); });
    
    while (true)
    {
        es.checkCollisions();
        es.createObjects();
    }
    return 0;
}
