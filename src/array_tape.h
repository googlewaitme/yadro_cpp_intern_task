#pragma once
#include <vector>
#include <cassert>
#include "base_tape.h"

template<typename T>
class ArrayTape: public BaseTape<T>
{
private:
	std::vector<T> _array;
	int _tape_position;
	int _size;
public:
	ArrayTape(std::vector<T> array) {
		_array = array;
		_size = array.size();
		_tape_position = 0;
	}

	int getTapePosition() {
		return _tape_position;
	}
	void moveTape(int step) {
		_tape_position += step;
		assert(_tape_position >= 0);
		assert(_tape_position < _size);
	}
	void write(T to_write_element) {
		_array[_tape_position] = to_write_element;
	}

	T read() {
		return _array[_tape_position];
	}
	T readDown() {
		moveTape(-1);
		return _array[_tape_position];
	}
	T readUp() {
		moveTape(1);
		return _array[_tape_position];
	}
};

