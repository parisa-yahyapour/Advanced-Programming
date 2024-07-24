main: main.o driver_missions_program.o space_for_missions.o mission.o driver.o error.o
	g++ --std=c++11 main.o driver_missions_program.o space_for_missions.o mission.o driver.o error.o -o main
main.o: main.cpp driver_missions_program.hpp mission.hpp driver.hpp space_for_missions.hpp error.hpp
	g++ -c --std=c++11 main.cpp
driver_missions_program.o: driver_missions_program.cpp driver_missions_program.hpp space_for_missions.hpp mission.hpp driver.hpp error.hpp
	g++ -c --std=c++11 driver_missions_program.cpp
space_for_missions.o: space_for_missions.cpp space_for_missions.hpp mission.hpp error.hpp
	g++ -c --std=c++11 space_for_missions.cpp
mission.o: mission.cpp mission.hpp error.hpp
	g++ -c --std=c++11 mission.cpp
driver.o: driver.cpp driver.hpp mission.hpp error.hpp
	g++ -c --std=c++11 driver.cpp
error.o: error.hpp error.cpp
	g++ -c --std=c++11 error.cpp
clean:
	rm *.o main.out