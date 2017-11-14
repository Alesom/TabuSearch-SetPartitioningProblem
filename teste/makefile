all: execute

execute: compile
	./Tabu < ../instances/spp_toy.txt

compile: headerfile
	g++ *.cpp -Wall -o Tabu

headerfile:
	g++ main.hpp -Wall

clear:
	rm *.gch
