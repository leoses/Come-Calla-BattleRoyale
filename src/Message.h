#include "Serializable.h"
#include  <string>
#include <SDL2/SDL.h>


enum class MessageType
{
    LOGIN   = 0,
    PLAYERPOS = 1,
    PICKUPEAT = 2,
    PLAYERTAM = 3,
    LOGOUT  = 4,
    UNDEFINED = 5
};

class Message: public Serializable{
public:
    
    Message();
    Message(MessageType type_);
    virtual ~Message();

    virtual void to_bin();
    virtual int from_bin(char * bobj);

    size_t getMessageSize();
    MessageType getMessageType();
    std::string getNick();
    void setNick(std::string newNick);

protected:
    static const size_t messageSize = sizeof(MessageType) + sizeof(char) * 8 + sizeof(SDL_Rect);
    MessageType type;
    SDL_Rect dimensions;
    std::string nick;

};