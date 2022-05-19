CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=VirtualMachine.cpp Source.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=vmachine

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
