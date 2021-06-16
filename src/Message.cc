#include "Message.h"
#include <memory.h>

Message::Message(): type(MessageType::UNDEFINED){

}
Message::Message(MessageType type_): type(type_){

}

Message::~Message(){

}

size_t Message::getMessageSize(){
    return messageSize;
}

MessageType Message::getMessageType(){
    return type;
}

void Message::to_bin(){
    alloc_data(messageSize);

    memset(_data, 0, messageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    memcpy(temp, nick.c_str(), sizeof(char) * 8);

    temp +=sizeof(char) * 8;

    memcpy(temp, &dimensions, sizeof(SDL_Rect)); 

}

int Message::from_bin(char * bobj){

    alloc_data(messageSize);

    memcpy(static_cast<void *>(_data), bobj, messageSize);

    //Reconstruir la clase usando el buffer _data
    char *temp = _data;

    //Copiamos tipo
    memcpy(&type, temp, sizeof(MessageType));
    temp += sizeof(MessageType);
    
    //Se puede hacer porque es un string (\0)
    nick = temp;
    temp +=sizeof(char) * 8;
    
    memcpy(&dimensions, temp, sizeof(SDL_Rect)); 
    return 0;
}

std::string Message::getNick(){
    return nick;
}

void Message::setNick(std::string newNick){
    nick = newNick;
}