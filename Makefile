CXX = g++
FLAGS = -std=c++20 -O3 -march=native -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -c main.cpp
	$(CXX) $(FLAGS) -c Examples/SpikeSlab.cpp
	$(CXX) -o main *.o
	rm -f *.o *.gch
