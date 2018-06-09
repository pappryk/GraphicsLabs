CXX=g++
CXXFLAGS+=-lsfml-graphics 
CXXFLAGS+=-lsfml-window
CXXFLAGS+=-lsfml-system
CXXFLAGS+=-lm
MAIN=sfml-app2
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)


all:
	g++ *.cpp -o $(MAIN) $(CXXFLAGS)

clean:
	rm -f $(MAIN) $(OBJ)

run:
	./$(MAIN)