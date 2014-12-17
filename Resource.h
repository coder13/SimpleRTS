#include <string>

class Resource {
private: 
	string _name;
	int _amount;

public:
	Resource(string name);
	Resource(string, int initialAmount);

	int add(int amount);

	int getAmount();

};