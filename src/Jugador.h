#include "Socket.h"
#include "SDLApp.h"
#include "Vector2D.h"

class Jugador{
private:
    SDLApp* playerApp;
    Socket socket;
    std::string nick;
    SDLTexture* texture = nullptr;
    Vector2D pos;
    SDL_Rect dimensions;
    int tam;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Jugador(const char * s, const char * p, const char * n);
    ~Jugador();

    void update();
    void login();
    void logout();
    void input_thread();
    void net_thread();
    std::string getNick(){return nick;}


};