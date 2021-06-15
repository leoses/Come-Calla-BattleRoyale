#include <thread>
#include "Jugador.h"

int main(int argc, char **argv)
{

    Jugador jug(argv[1], argv[2], argv[3]);

    while(true){
        //std::cout << "aqui iria el update del jugador por ejemplo\n";
    }

    //std::thread net_thread([&ec](){ ec.net_thread(); });

    //ec.login();

    //ec.input_thread();
}

