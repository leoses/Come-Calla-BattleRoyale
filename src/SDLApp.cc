#include "SDLApp.h"
#include "iostream"
#include <SDL2/SDL.h>
#include "Resources.h"

SDLApp* SDLApp::instance = nullptr;

SDLApp::SDLApp(){
    initSDL();
	initResources();
}

SDLApp::~SDLApp(){
	//Destruimos textureManager
	delete textureManager_;

    //Destruimos render y window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	//Cerramos SDL
	SDL_Quit();
}

void SDLApp::initSDL(){
    int winX, winY; // PosiciOn de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// InicializaciOn del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Come&Calla", winX, winY, winWidth_,
		winHeight_, SDL_WINDOW_SHOWN);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) {
		std::cout<< "Game window or renderer was null \n";
	}
}

SDLApp* SDLApp::GetInstance()
{
	if(instance==nullptr){
    	instance = new SDLApp();
    }
    return instance;
}

SDL_Window* SDLApp::getWindow(){
	return window_;
}

SDL_Renderer* SDLApp::getRenderer(){
	return renderer_;
}

void SDLApp::initResources(){

	//Crear e inicializar textureManager
	textureManager_ = new TextureManager();
	textureManager_->initObject();

	//Creacion de las texturas
	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
	}
}