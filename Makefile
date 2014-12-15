INCLUDE = -I/usr/include/

COMPILERFLAGS = -Wall
CC = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBS = -lglut -lGL -lGLU -lm

game: game.cpp Chunk.o
	$(CC) game.cpp $(CXXFLAGS) world/Chunk.cpp -o game $(LIBS) -lstdc++

Chunk.o: world/Chunk.cpp Vec3f.o
	$(CC) -c world/Chunk.cpp Vec3f.o $(LIBS)

Vec3f.o: util/Vec3f.cpp util/Vec3f.h
	$(CC) -c util/Vec3f.cpp util/Vec3f.h