all: compile assemble clean msg

compile:
	@g++ -c main.cpp headers/Edges.cpp headers/Corners.cpp headers/Cube.cpp

assemble:
	@g++ main.o Edges.o Corners.o Cube.o -o mono

clean:
	@rm *.o
msg:
	@echo "Execute ./mono"


