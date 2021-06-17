#include "Resources.h"

//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
vector<Resources::ImageInfo> Resources::imageRoutes {

	//Botones
	{ Escenario, "./Assets/Escenario.png" },
	{ Jugador1, "./Assets/Jugador01.png" },
	{ Jugador2, "./Assets/Jugador02.png" },
	
};
/*
//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
vector<Resources::AudioInfo> Resources::audioRoutes{
	//Musica principal

};

vector<Resources::AudioVolume> Resources::audioVolume{
	
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	{// RETRO, "../Sources/fonts/RetroGaming.ttf", GameManager::instance()->getFontSize() },
	//Para añadir nueva ruta: {FontId, "./Sources/fonts/name.ttf", size}
};

vector <Resources::TextMsgInfo> Resources::messages{
	//Para añadir nuevo texto: {TextureId , string "mensaje", { COLOR(0xaaffffff), FontId  }
};*/

