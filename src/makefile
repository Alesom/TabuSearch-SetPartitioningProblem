all: execute

execute: compile
	./Tabu < ../instances/sppnw08.txt

compile: headerfile
	g++ *.cpp -Wall -o Tabu

headerfile:
	g++ main.hpp -Wall

clear:
	rm *.gch
