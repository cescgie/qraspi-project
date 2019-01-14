.PHONY: clean debug run

CXX = g++
CXXFLAGS = -std=c++11 -march=native -O3 
LDFLAGS =

SOURCES = othello.cpp game.cpp board.cpp player.cpp heuristic.cpp database.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = othello 

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) debug *.stackdump *~ *.dSYM/

debug:
	$(CXX) $(CXXFLAGS) -g -o debug $(SOURCES)

run:
	./$(EXECUTABLE)
