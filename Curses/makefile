CC = gcc
CFLAGS = -W -Wall
LIB = -lncursesw -lpanel -lmenu -lform
SRCS1 = main.c
EXE1 = curses
HEADER = includes
EXT = *.o

$(EXE1): $(SRCS1)
	clear
	$(CC) $(CFLAGS) $(SRCS1) -o $(EXE1) $(LIB)

clean:
	rm -f $(EXT)
