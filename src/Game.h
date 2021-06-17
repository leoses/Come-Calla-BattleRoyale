#include "Jugador.h"
#include "SDLApp.h"
#include "PlayerInfo.h"
#include <map>

class Game{
private:
    //Jugador controlado por este juego
    Jugador* mainPlayer = nullptr;
    //Lista con la informacion de los otros jugadores
    std::map<std::string, PlayerInfo> jugadores;
    //Referencia a la App de SDL para gestionar el pintado, la ventana etc
    SDLApp* app = nullptr;

    void render()const;

public:
    Game(const char *s, const char *p, const char *n);
    ~Game();

    void initGame();
    void net_thread();
    void input_thread();

};