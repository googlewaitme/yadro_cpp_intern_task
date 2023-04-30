
#pragma once
#include <fstream>


template<typename T>
class BaseTape
{
private:
	int _size;
	int _tape_position;

public:
	BaseTape() {};
	~BaseTape() {};

	int getTapePosition();
	virtual void moveTape(int step) = 0;
	virtual void write(T to_write_element) = 0;
	virtual T read() = 0;
	virtual T readDown() = 0;
	virtual T readUp() = 0;
};
