#include "Tile.h"

Tile::Tile(int id, string name) {
	ID = id;
	_name = name;
}


Tiles[0] = Tile(0, "Air");
Tiles[1] = Tile(1, "Grass");
Tiles[2] = Tile(2, "Stone");
Tiles[3] = ResourceTile(3, "Mineral");