#include "SDL.h"

class SDLApp
{
private:
	///<summary>Variables basicas de SDL</summary>
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

    void initSDL();

public:
    SDLApp();
    ~SDLApp();

    ///<summary>Constantes con las dimensiones de la ventana </summary>
	static const int winWidth_ = 800;
	static const int winHeight_ = 600; 
}