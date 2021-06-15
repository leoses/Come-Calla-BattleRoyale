#include "GameServer.h"

int main(int argc, char **argv)
{
    std::cout << "creacion del game server\n";
    GameServer es(argv[1], argv[2]);
    std::cout << "Se ha creado correctamente\n";

    es.do_messages();

    return 0;
}
