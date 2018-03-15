CXX=g++
CXXFLAGS+=-lsfml-graphics 
CXXFLAGS+=-lsfml-window
CXXFLAGS+=-lsfml-system
CXXFLAGS+==lm
MAIN=sfml-app
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)


all:
	g++ *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(MAIN) $(OBJ)

run:
	./$(MAIN)