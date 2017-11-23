all: execute

execute: compile
	./Tabu < ../instances/sppaa04.txt

compile: headerfile
	g++ *.cpp -Wall -o Tabu

headerfile:
	g++ main.hpp -Wall

clear:
	rm *.gch
