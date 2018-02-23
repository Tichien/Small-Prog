CC = gcc
CFLAGS = -W -Wall
SRCS1 = srcs/sshell.c srcs/shell.c
SRCS2 = srcs/cshell.c srcs/shell.c
EXE1 = sshell
EXE2 = cshell
HEADER = includes
EXT = *.o

all: $(EXE1) $(EXE2) 

$(EXE1): $(SRCS1)
	clear
	clear
	$(CC) $(SRCS1) -o $(EXE1) -I $(HEADER) $(CFLAGS) 

$(EXE2): $(SRCS2)
	clear
	$(CC) $(SRCS2) -o $(EXE2) -I $(HEADER) $(CFLAGS) 

clean:
	rm -f $(EXT) $(BIN)
