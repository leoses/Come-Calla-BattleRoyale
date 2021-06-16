#include "Jugador.h"
#include "Message.h"

Jugador::Jugador(const char * s, const char * p, const char * n):socket(s,p),nick(n)
{
    //conectarse al servidor mediante login
    login();

    //Guardas referencia a la aplicacion
    playerApp = SDLApp::GetInstance();

    //inicializar textura
    texture =  new SDLTexture();
}

Jugador::~Jugador(){
    //Borrar el singleton del SDLApp
    delete playerApp;
    //Borrar textura del jugador
    delete texture;
}

void Jugador::update(){

}

void Jugador::login(){
    Message logMsg = Message(MessageType::LOGIN);
    logMsg.setNick(nick);
    if(socket.send(logMsg, socket) == -1){
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

void Jugador::logout(){

}

void Jugador::input_thread()
{
    while (true)
    {
        /*
        // Leer stdin con std::getline
        std::string msg;
        std::getline(std::cin, msg);

        //Mensaje de tam maximo 80 caracteres
        if (msg.size() > 80) msg.resize(80);

        //Creamos objeto serializable
        ChatMessage em(nick, msg);
        em.type = ChatMessage::MESSAGE;

        // Enviar al servidor usando socket
        socket.send(em, socket);
        */
    }
}

void Jugador::net_thread()
{
    while (true)
    {
        /*
        //Recibir Mensajes de red
        ChatMessage em;

        socket.recv(em);

        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        std::cout << em.nick << ": " << em.message << "\n";
        */
    }
}