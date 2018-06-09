CXX=g++
CXXFLAGS+=wx-config
CXXFLAGS+=--cxxflags
CXXFLAGS+=--libs
MAIN=wx-app
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

program:
	g++ *.cpp `wx-config --cxxflags --libs` -o wx-app


class:
	touch $(cn).h $(cn).cpp
	echo "#pragma once" > $(cn).h
	echo "#include \"$(cn).h\"" > $(cn).cpp
	echo "class $(cn)" >> $(cn).h
	echo "{" >> $(cn).h
	echo "};" >> $(cn).h

clean:
	rm -f $(MAIN) $(OBJ)

run:
	./$(MAIN)