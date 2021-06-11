#include <thread>
#include "Chat.h"
#include <SDL2/SDL.h>
#include "SDLApp.h"

int main(int argc, char **argv)
{

    SDLApp* app = new SDLApp();

    ChatClient ec(argv[1], argv[2], argv[3]);

    std::thread net_thread([&ec](){ ec.net_thread(); });

    ec.login();

    ec.input_thread();
}

