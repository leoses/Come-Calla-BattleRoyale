#include "Message.h"
#include <memory.h>
#include "Jugador.h"

Message::Message(): type(MessageType::UNDEFINED){

}
Message::Message(MessageType type_, Jugador* player_): type(type_),player(player_){

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
    switch(type){
        case MessageType::LOGIN:
        {
            //calculamos el tamaño del mensaje
            
            messageSize = sizeof(MessageType) + sizeof(char)*12;
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
             memcpy(temp, player->getNick().c_str(), sizeof(char) * 12);

            break;
        }

             case MessageType::LOGOUT:
        {
            //calculamos el tamaño del mensaje
            
            messageSize = sizeof(MessageType) + sizeof(char)*12;
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
             memcpy(temp, player->getNick().c_str(), sizeof(char) * 12);

            break;
        }
    
    }
   
}

int Message::from_bin(char * bobj){

//reservamos memoria para coger el tipo de mensaje
    messageSize= sizeof(MessageType);
    alloc_data(messageSize);
//coger el tipo de mensaje
    memcpy(static_cast<void *>(_data), bobj, messageSize);

    //Reconstruir la clase usando el buffer _data
    char *temp = _data;

    //Copiamos tipo
    memcpy(&type, temp, sizeof(MessageType));
    

    switch(type){
        case MessageType::LOGIN:
        {
            messageSize = sizeof(MessageType) + sizeof(char)*12;
            //reservamos la memoria
            alloc_data(messageSize);
            memcpy(static_cast<void *>(_data), bobj, messageSize);
             //Reconstruir la clase usando el buffer _data
            char *temp = _data;
            temp += sizeof(MessageType);
             //Se puede hacer porque es un string (\0)
            nick = temp;
            break;
        }

          case MessageType::LOGOUT:
        {
            messageSize = sizeof(MessageType) + sizeof(char)*12;
            //reservamos la memoria
            alloc_data(messageSize);
            memcpy(static_cast<void *>(_data), bobj, messageSize);
             //Reconstruir la clase usando el buffer _data
            char *temp = _data;
            temp += sizeof(MessageType);
             //Se puede hacer porque es un string (\0)
            nick = temp;
            break;
        }
    }
    
  
    
   
    return 0;
}

std::string Message::getNick(){
    return nick;
}

void Message::setNick(std::string newNick){
    nick = newNick;
}