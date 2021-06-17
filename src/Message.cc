#include "Message.h"
#include <memory.h>
#include "Jugador.h"

Message::Message() : type(MessageType::UNDEFINED)
{
}
Message::Message(MessageType type_, Jugador *player_) : type(type_), player(player_)
{
    nick = player->getNick();
}

Message::~Message()
{
}

size_t Message::getMessageSize()
{
    return messageSize;
}

MessageType Message::getMessageType()
{
    return type;
}

void Message::to_bin()
{
    switch (type)
    {
    case MessageType::LOGIN:
    {
        serializeTypeNick();
        break;
    }

    case MessageType::LOGOUT:
    {
        serializeTypeNick();
        break;
    }

    case MessageType::PLAYERINFO:
    {
        serializePlayerInfo();
         break;
    }

    case MessageType::NEWPLAYER:
    {
        serializePlayerInfo();
        break;
    }
    }
}

int Message::from_bin(char *bobj)
{

    //reservamos memoria para coger el tipo de mensaje
    messageSize = sizeof(MessageType);
    alloc_data(messageSize);
    //coger el tipo de mensaje
    memcpy(static_cast<void *>(_data), bobj, messageSize);

    //Reconstruir la clase usando el buffer _data
    char *temp = _data;

    //Copiamos tipo
    memcpy(&type, temp, sizeof(MessageType));

    switch (type)
    {
    case MessageType::LOGIN:
    {
        std::cout << "LOGIN\n";
        constructTypeNick(bobj);
        break;
    }

    case MessageType::LOGOUT:
    {
        std::cout << "LOGOUT\n";
        constructTypeNick(bobj);
        break;
    }

    case MessageType::PLAYERINFO:
    {
        constructPlayerInfo(bobj);
        break;
    }

    case MessageType::NEWPLAYER:
    {
        std::cout << "NEWPLAYER\n";
        constructPlayerInfo(bobj);
        break;
    }

    default:
        std::cout << "Ni LOG ni LOGOUT\n";
        break;
    }

    return 0;
}

std::string Message::getNick()
{
    return nick;
}

void Message::setNick(std::string newNick)
{
    nick = newNick;
}

void Message::setMsgType(MessageType type_)
{
    type = type_;
}

void Message::serializeTypeNick()
{
    //calculamos el tamaño del mensaje

    messageSize = sizeof(MessageType) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(messageSize);
    memset(_data, 0, messageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);
}

void Message::serializePlayerInfo()
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(double)*2 + sizeof(int);
    //reservamos la memoria
    alloc_data(messageSize);

    memset(_data, 0, messageSize);


    //Serializar los campos type
    char *temp = _data;


    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));


    temp += sizeof(MessageType);


    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);

    temp += sizeof(char) * 12;

    float x = playerInfo.pos.getX();
    memcpy(temp, &x, sizeof(double));
    temp += sizeof(double);

    float y = playerInfo.pos.getY();
    memcpy(temp, &y, sizeof(double));
    temp += sizeof(double);

    memcpy(temp, &playerInfo.tam, sizeof(int));
}

void Message::constructTypeNick(char *bobj)
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(messageSize);
    memcpy(static_cast<void *>(_data), bobj, messageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;
}

void Message::constructPlayerInfo(char *bobj)
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(double)*2 + sizeof(int);
    //reservamos la memoria
    alloc_data(messageSize);
    memcpy(static_cast<void *>(_data), bobj, messageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;

    temp += sizeof(char) * 12;

    float x, y;
    memcpy(&x, temp, sizeof(double));
    temp += sizeof(double);
    memcpy(&y, temp, sizeof(double));
    temp += sizeof(double);
    int tam;
    memcpy(&tam, temp, sizeof(int));

    playerInfo.tam = tam;

    playerInfo.pos.setX(x);
    playerInfo.pos.setY(y);


}