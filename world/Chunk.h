const int CHUNK_SIZE = 16;

class Chunk {
private: 
	int map[CHUNK_SIZE*CHUNK_SIZE];
	int X, Y, list;
public: 
	Chunk(int x, int y);
	void gen();
	int getX();
	int getY();
	int combine();
	int getId(int x, int y);
	bool setId(int x, int y, int id);
	void draw();

};