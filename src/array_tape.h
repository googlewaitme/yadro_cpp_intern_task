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

	int getTapePosition() override {
		return _tape_position;
	}

	int getSize() override {
		return _size;
	}

	void moveTape(int step) override {
		_tape_position += step;
		assert(_tape_position >= 0);
		// TODO question <= or < ? 
		assert(_tape_position <= _size);
	}
	void write(T to_write_element) override {
		_array[_tape_position] = to_write_element;
	}

	T read() override {
		return _array[_tape_position];
	}
	T readDown() override {
		return _array[_tape_position--];
	}
	T readUp() override {
		// TODO change to moveTape
		return _array[_tape_position++];
	}
};

