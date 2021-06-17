#include <thread>
#include "Jugador.h"
#include "InputManager.h"

int main(int argc, char **argv)
{

    Jugador jug(argv[1], argv[2], argv[3]);
    
    //Iniciamos el thread que se encargará de recibir mensajes del
    //servidor
    std::thread net_thread([&jug](){ jug.net_thread(); });

    //Mandamos el mensaje de login, creamos la ventana de SDL etc
    jug.initPlayer();

    //Para que se quede aquí hasta que queramos
    while(true){
        //std::cout << "aqui iria el update del jugador por ejemplo\n";
    }

    //ec.input_thread();
}

