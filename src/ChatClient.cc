#include <thread>
#include "Game.h"

int main(int argc, char **argv)
{

    Game game(argv[1],argv[2], argv[3]);

    //Iniciamos el thread que se encargará de recibir mensajes del
    //servidor
    std::thread([&game]() { game.net_thread(); }).detach();
    
    //Mandamos mensaje de login y creamos la ventana de SDL
    game.initGame();

    //Para que se quede aquí hasta que queramos
    game.run();

    return 0;
}

