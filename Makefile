CXX = g++
CXXFLAGS = -Iinclude
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.o Game.o Snek.o Apple.o
	$(CXX) main.o Game.o Snek.o Apple.o -o main $(LDFLAGS)

main.o: main.cpp Game.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Snek.o: Snek.cpp Snek.h
	$(CXX) $(CXXFLAGS) -c Snek.cpp

Apple.o: Apple.cpp Apple.h
	$(CXX) $(CXXFLAGS) -c Apple.cpp
clean:
	rm -f *.o main