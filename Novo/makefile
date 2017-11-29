all: execute

execute: compile
	./Tabu < ../instances/antigas/spp_toy.txt

compile: headerfile
	g++ *.cpp -Wall -std=c++11 -o Tabu

headerfile:
	g++ main.hpp -std=c++11 -Wall

clear:
	rm *.gch
