#include "GameObject.h"
#include "SDLApp.h"

GameObject::GameObject(Vector2D pos_,int id_,int tam_):pos(pos_), id(id_), tam(tam_)
{
    //textura = new Texture(SDLApp::GetInstance()->getRenderer(), )
    dimensions = SDL_Rect({(int)pos.getX(), (int)pos.getY(), 100,100});
}

GameObject::~GameObject(){

}