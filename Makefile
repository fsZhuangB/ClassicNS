CXX = g++-9
FLAGS = -std=c++2a -O3 -march=native -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -c SqliteDB.cpp
	$(CXX) $(FLAGS) -c main.cpp
	$(CXX) $(FLAGS) -c Examples/SpikeSlab.cpp
	$(CXX) -o main *.o -lsqlite3
	rm -f *.o *.gch
