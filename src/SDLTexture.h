#include <SDL2/SDL_image.h>

#include <string>
using namespace std;

class SDLTexture {
private:
	SDL_Texture* texture_;
	SDL_Renderer* renderer_;
	int width_;
	int height_;

public:
	SDLTexture();
	SDLTexture(SDL_Renderer* renderer, const string& fileName);
	//SDLTexture(SDL_Renderer* renderer, const string& text, const Font* font, const SDL_Color& color);
	SDLTexture(SDL_Renderer* renderer, SDL_Surface* src, SDL_Rect* srcRect, SDL_Surface* dest, SDL_Rect* destRect);

	virtual ~SDLTexture();

	inline int getWidth() {
		return width_;
	}

	inline int getHeight() {
		return height_;
	}

	inline bool isReady() {
		return texture_ != nullptr;
	}

	// Carga las texturas a partir de una imagen
	bool loadFromImg(SDL_Renderer* renderer, const string& fileName);

	//Carga las texturas a partir de un texto con una fuente
	//bool loadFromText(SDL_Renderer* renderer, const string& text, const Font* font, const SDL_Color& color = { 0, 0, 0, 255 });

	//Carga texturas a partir de dos surface para hacer un blit
	bool loadFromSurface(SDL_Renderer* renderer, SDL_Surface* src, SDL_Rect* srcRect, SDL_Surface* dest, SDL_Rect* destRect);

	//Renderiza en posiciones directamente
	void render(int x, int y) const;

	//Renderiza un frame de la textura en el destRect, si no hay frame se renderiza toda la textura
	void render(const SDL_Rect& dest) const;
	void render(const SDL_Rect& dest, const SDL_Rect& frame) const;

	// Renderiza un frame de la textura en el destRect con una rotación, si no hay frame se renderiza toda la textura con un ángulo
	void render(const SDL_Rect& dest, double angle, const SDL_Rect& frame) const;
	void render(const SDL_Rect& dest, double angle) const;
	//Devuelve el SDL_Texture
	SDL_Texture* getSDLTex() { return texture_; }

	void close();
};