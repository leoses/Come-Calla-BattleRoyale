#include "Serializable.h"
#include  <string>

enum class MessageType
{
    LOGIN   = 0,
    PLAYERPOS = 1,
    PICKUPEAT = 2,
    PLAYERTAM = 3,
    LOGOUT  = 4
};

class Message: public Serializable{
public:
    
    Message(MessageType type_);
    virtual ~Message();

    virtual void to_bin() = 0;
    virtual int from_bin(char * bobj) = 0;

    size_t getMessageSize();
    MessageType getMessageType();

protected:
    size_t messageSize = 0;
    MessageType type;

};

class LoginMessage : public Message{
private:
    std::string nick;
public:
    LoginMessage(std::string nick_);
    virtual ~LoginMessage();
    virtual void to_bin() override;
    virtual int from_bin(char * bobj) override;
    std::string getNick();

};