CC = g++
CFLAGS = -W -Wall
LIB = -lncursesw
SRCS1 = main.cpp unidraw.cpp
EXE1 = curses
HEADER = includes
EXT = *.o

$(EXE1): $(SRCS1)
	clear
	$(CC) $(CFLAGS) $(SRCS1) -o $(EXE1) $(LIB)

clean:
	rm -f $(EXT)
