INCLUDE = -I/usr/include/

COMPILERFLAGS = -Wall
CC = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBS = -lglut -lGL -lGLU -lm

game: *.cpp util/*.cpp world/*.cpp
	$(CC) $(CXXFLAGS) $^ -o game $(LIBS) -lstdc++
