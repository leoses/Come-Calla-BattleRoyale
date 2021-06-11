#include <SDL2/SDL.h>

class SDLApp
{
private:
	///<summary>Variables basicas de SDL</summary>
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

    void initSDL(){

		int winX, winY; // PosiciOn de la ventana
		winX = winY = SDL_WINDOWPOS_CENTERED;
		// InicializaciOn del sistema, ventana y renderer
		SDL_Init(SDL_INIT_EVERYTHING);
		window_ = SDL_CreateWindow("Dopplebanger", winX, winY, winWidth_,
		winHeight_, SDL_WINDOW_SHOWN);
		std::cout<< "ventana creada \n";

		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
		std::cout<< "renderer creada \n";
		if (window_ == nullptr || renderer_ == nullptr) {
			std::cout<< "Game window or renderer was null \n";
		}

	};

public:
    SDLApp(){
		   initSDL();
	};
    ~SDLApp(){

		//Destruimos render y window
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);

		renderer_ = nullptr;
		window_ = nullptr;

		//Cerramos SDL
		SDL_Quit();
	};

    ///<summary>Constantes con las dimensiones de la ventana </summary>
	static const int winWidth_ = 800;
	static const int winHeight_ = 600; 
};