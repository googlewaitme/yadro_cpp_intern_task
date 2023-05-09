#pragma once

#include <vector>
#include <cassert>
#include <iostream>

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

	void print_array() override {
		for (int i=0; i<_size; i++) {
			std::cout << _array[i] << " ";
		}
		std::cout << std::endl;
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
		T to_return_value = _array[_tape_position];
		moveTape(-1);
		return to_return_value;
	}
	T readUp() override {
		T to_return_value = _array[_tape_position];
		moveTape(1);
		return to_return_value;
	}
};

