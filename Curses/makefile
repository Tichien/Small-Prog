CC = g++
CFLAGS = -W -Wall -g
SRCS1 = main.cpp Canvas.cpp Turtle.cpp Color.cpp Attr.cpp Cell.cpp Window.cpp Term.cpp
LIB = -lncursesw
EXE1 = test
HEADER = includes
EXT = *.o

$(EXE1): $(SRCS1)
	clear
	$(CC) $(CFLAGS) $(SRCS1) -o $(EXE1) $(LIB)

clean:
	rm -f $(EXT)
