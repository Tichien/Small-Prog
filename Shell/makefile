CC = g++
CFLAGS = -W -Wall
SRCS1 = sshell.cpp file.cpp
SRCS2 = cshell.cpp file.cpp
EXE1 = sshell
EXE2 = cshell
EXT = *.o

all: $(EXE1) $(EXE2) 

$(EXE1): $(SRCS1)
	clear
	clear
	$(CC) $(SRCS1) -o $(EXE1) $(CFLAGS) 

$(EXE2): $(SRCS2)
	clear
	$(CC) $(SRCS2) -o $(EXE2) $(CFLAGS) 

clean:
	rm -f $(EXT) $(BIN)
