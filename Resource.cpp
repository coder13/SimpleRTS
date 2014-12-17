#include "Resource.h"

Resource::Resource(String name) {
	_name = name;
	_amount = 0;
}

Resource::Resource(String name, int initialAmount) {
	_name = name;
	_amount = initialAmount;
}


int Resource::add(int amount) {
	_amount += amount;
	return _amount;
} 

int Resource::getAmount() {
	return _amount;
}