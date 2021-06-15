#include "GameServer.h"

int main(int argc, char **argv)
{
    GameServer es(argv[1], argv[2]);
    std::cout << "Creacion del game server completada\n";

    es.do_messages();

    return 0;
}
