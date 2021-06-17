#include <thread>
#include "Game.h"

int main(int argc, char **argv)
{

    Game game(argv[1],argv[2], argv[3]);

    std::cout << "Iniciamos el thread de escucha del juego\n";
    //Iniciamos el thread que se encargará de recibir mensajes del
    //servidor
    std::thread net_thread([&game]() { game.net_thread(); });
    //Mandamos mensaje de login y creamos la ventana de SDL
    game.initGame();
    //thread para escuchar al input
    game.input_thread();

    //Para que se quede aquí hasta que queramos
    while(true){
        //std::cout << "aqui iria el update del jugador por ejemplo\n";
    }

    //ec.input_thread();


}

