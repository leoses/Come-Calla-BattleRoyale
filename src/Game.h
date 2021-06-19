#include "Jugador.h"
#include "SDLApp.h"
#include "ObjectInfo.h"
#include <map>
#include "Socket.h"

class Game
{
private:
    //Jugador controlado por este juego
    Jugador *mainPlayer = nullptr;
    //Lista con la informacion de los otros jugadores
    std::map<std::string, ObjectInfo> jugadores;
    //Lista de informacion de los objetos
    std::map<std::string, ObjectInfo> objetos;
    //Referencia a la App de SDL para gestionar el pintado, la ventana etc
    SDLApp *app = nullptr;
    //Textura de fondo
    SDLTexture *background = nullptr;
    //SOcket para comunicarnos con el servidor
    Socket socket;

    //booleano para determinar si hemos perdido o no
    bool isRunning = true;

public:
    Game(const char *s, const char *p, const char *n);
    ~Game();

    void render() const;
    void initGame();
    void net_thread();
    void input_thread();
    void run();
};