CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = opendirectory.h commandmode.h
OBJ = opendirectory.o commandmode.o fileExpo.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fileExpo: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

