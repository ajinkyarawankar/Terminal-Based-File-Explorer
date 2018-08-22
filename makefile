CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = opendirectory.h
OBJ = opendirectory.o fileExpo.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fileExpo: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

