DEPS = Vector2D.h  Resources.h SDLTexture.h TextureManager.h Socket.h Message.h GameServer.h SDLApp.h Jugador.h GameObject.h ChatClient.h ChatServer.h

SERVER = Vector2D.o  Resources.o Socket.o Message.o GameServer.o
CLIENT = Vector2D.o  Resources.o SDLTexture.o TextureManager.o Socket.o Message.o SDLApp.o Jugador.o GameObject.o
#LINKER_FLAGS specifies the libraries we're linking against
LIBS =  -lpthread 
LIBSSDL=-lSDL2 -lSDL2_image -lSDL2_ttf
%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
all: cs cc
cs: $(SERVER) ChatServer.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
cc: $(CLIENT) ChatClient.o
	g++ -o $@ $^ $(CFLAGS) `pkg-config --cflags --libs sdl2` $(LIBS) $(LIBSSDL) 
.PHONY: clean
clean:
	rm -f *.o server client