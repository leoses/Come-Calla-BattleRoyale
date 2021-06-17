#pragma once
#include "Serializable.h"
#include  <string>
#include <SDL2/SDL.h>
#include "PlayerInfo.h"
class Jugador;


enum class MessageType
{
    LOGIN   = 0,
    PLAYERINFO = 1,
    PICKUPEAT = 2,
    NEWPICKUP = 3,
    PICKUPDESTROY = 4,
    LOGOUT  = 5,
    NEWPLAYER =6,
    UNDEFINED = 7
};

class Message: public Serializable{
protected:
    size_t messageSize = sizeof(MessageType);
    MessageType type;
    SDL_Rect dimensions;
    std::string nick;
    Jugador* player;
    PlayerInfo playerInfo;

    //Metodos para la serializacion de nuestros mensajes
    void serializeTypeNick();
    void serializePlayerInfo();

    //Metodos para la construccion de los mensajes recibidos
    void constructTypeNick(char *bobj);
    void constructPlayerInfo(char *bobj);

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
    PlayerInfo getPlayerInfo()const{
        return playerInfo;
    }
    
    void setNick(std::string newNick);
    void setPlayerInfo(const PlayerInfo& info){
        playerInfo = info;
    }
    void setMsgType(MessageType type);

};