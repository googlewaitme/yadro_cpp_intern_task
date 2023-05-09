
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

	virtual int getTapePosition() = 0;
	virtual int getSize() = 0;
	virtual void moveTape(int step) = 0;
	virtual void write(T to_write_element) = 0;
	virtual T read() = 0;
	virtual T readDown() = 0;
	virtual T readUp() = 0;
	// TODO delete me
	
	virtual void print_array() = 0;
};
