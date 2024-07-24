turtix.out: main.o game.o creature.o map.o
	g++ --std=c++11 main.o game.o creature.o map.o -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -o turtix.out
main.o: game.hpp main.cpp map.hpp creature.hpp
	g++ -c --std=c++11 main.cpp
game.o: game.cpp game.hpp map.hpp creature.hpp
	g++ -c --std=c++11 game.cpp
creature.o: creature.cpp creature.hpp
	g++ -c --std=c++11 creature.cpp
map.o: map.hpp map.cpp
	g++ -c --std=c++11 map.cpp
clean:
	rm *.o turtix.out