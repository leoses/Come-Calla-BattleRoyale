#pragma once
#include "Serializable.h"
#include  <string>
#include <SDL2/SDL.h>

class Jugador;


enum class MessageType
{
    LOGIN   = 0,
    PLAYERINFO = 1,
    PICKUPEAT = 2,
    NEWPICKUP = 3,
    PICKUPDESTROY = 4,
    LOGOUT  = 5,
    UNDEFINED = 6
};

class Message: public Serializable{
public:
    
    Message();
    Message(MessageType type_ ,Jugador* player_);
    //Message(MessageType type_ PickUp obj);
    virtual ~Message();

    virtual void to_bin();
    virtual int from_bin(char * bobj);

    size_t getMessageSize();
    MessageType getMessageType();
    std::string getNick();
    void setNick(std::string newNick);

protected:
    size_t messageSize = sizeof(MessageType);
    MessageType type;
    SDL_Rect dimensions;
    std::string nick;
    Jugador* player;
    

};