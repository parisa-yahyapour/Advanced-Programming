futballFantasy.out : main.o FutballFantasy.o Team.o Player.o WeekTable.o Match.o Database.o User.o Admin.o io_handler.o ErrorHandler.o TransferTable.o
	g++ --std=c++11 main.o FutballFantasy.o Team.o Player.o WeekTable.o Match.o Database.o User.o Admin.o io_handler.o ErrorHandler.o TransferTable.o -o futballFantasy.out
main.o : main.cpp FutballFantasy.hpp WeekTable.hpp User.hpp Database.hpp io_handler.hpp magic_number.hpp Match.hpp Team.hpp Player.hpp TransferTable.hpp
	g++ --std=c++11 -c main.cpp
FutballFantasy.o : FutballFantasy.cpp FutballFantasy.hpp WeekTable.hpp User.hpp Database.hpp io_handler.hpp magic_number.hpp Match.hpp Team.hpp Player.hpp ErrorHandler.hpp TransferTable.hpp
	g++ --std=c++11 -c FutballFantasy.cpp
Team.o : Team.cpp Team.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c Team.cpp
Player.o : Player.cpp Player.hpp Team.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c Player.cpp
WeekTable.o : WeekTable.cpp WeekTable.hpp Match.hpp Team.hpp Player.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c WeekTable.cpp
Match.o : Match.cpp Match.hpp Team.hpp Player.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c Match.cpp
Database.o : Database.cpp Database.hpp WeekTable.hpp Team.hpp Player.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c Database.cpp
User.o : User.cpp User.hpp Team.hpp Player.hpp magic_number.hpp TransferTable.hpp
	g++ --std=c++11 -c User.cpp
Admin.o : Admin.cpp Admin.hpp
	g++ --std=c++11 -c Admin.cpp
io_handler.o : io_handler.cpp io_handler.hpp 
	g++ --std=c++11 -c io_handler.cpp
ErrorHandler.o : ErrorHandler.cpp ErrorHandler.hpp
	g++ --std=c++11 -c ErrorHandler.cpp
TransferTable.o : TransferTable.cpp TransferTable.hpp magic_number.hpp Player.hpp Team.hpp
	g++ --std=c++11 -c TransferTable.cpp
clean :
	rm *.o futballFantasy.out