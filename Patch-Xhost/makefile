CC = g++
CFLAGS = -W -Wall
SRCS1 = patch.cpp
SRCS2 = depatch.cpp
EXT = *.o

all: patch depatch

patch: patch.cpp
	$(CC) $(SRCS1) -o patch $(CFLAGS) 

depatch: depatch.cpp
	$(CC) $(SRCS2) -o depatch $(CFLAGS) 

clean:
	rm -f $(EXT) $(BIN)