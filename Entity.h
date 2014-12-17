#include "util/Vec3f.h"

class Entity {
private: 
	Vec3f _pos;
	int list;

	Vec3f target;
	bool targetReached;
public:
	Entity();
	Entity(Vec3f pos);
	void tick();
	void draw();

	void setTarget(Vec3f t);
	bool reachedTarget();
};