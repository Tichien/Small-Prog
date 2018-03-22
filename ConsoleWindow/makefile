CC = g++
CFLAGS = -W -Wall
SRCS = main.cpp Rect.cpp Clock.cpp Color.cpp Attribute.cpp Cellule.cpp Window.cpp ConsoleScreen.cpp ConsoleWindow.cpp Console.cpp Keyboard.cpp Mouse.cpp pdcurses.lib 
OBJS = $(SRCS:.cpp = .o)
BIN = pc
EXT = *.o

all: $(OBJS)
	clear
	clear
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LIB)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(EXT) $(BIN)
