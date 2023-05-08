#include "solution.h"
#include "base_tape.h"
#include "array_tape.h"
#include <vector>
#include <iostream>
#include <algorithm>


Solution::Solution(
		int ram_size, 
		BaseTape<int>* input,
		BaseTape<int>* output,
		BaseTape<int>* temp1,
		BaseTape<int>* temp2
	)
{
	// TODO change temp1, temp2 to array of temps
	_ram_size = ram_size;
	_ram_count_elements = 0;
	_ram_vector = std::vector<int> (_ram_size);

	_input = input;
	_output = output;

	_input_size = _input->getSize();

	_temp1 = temp1;
	_temp2 = temp2;
}


void Solution::sortTape() {
	// Сортируем по K чисел на временные ленты
	inputData();
	// while( not sorted ):
	//    merge(TempTape1, TempTape2, output);
	//    sorted = split(output, TempTape1, TempTape2);
}


void Solution::inputData() {
	int count_of_full_sets = _input_size / _ram_size;
	if (_input_size % _ram_size > 0)
		count_of_full_sets += 1;
	for (int i=0; i < count_of_full_sets; i++) {
		readInRam();
		sortRam();

		printRam();
		// TODO change to array of tapes;
		if (i % 2 == 0) {
			writeRamToTape(_temp1);
		} else {
			writeRamToTape(_temp2);
		}
		// writeRamToTape();
	}
}


void Solution::readInRam() {
	int left_elements_in_input = _input->getSize() - _input->getTapePosition();
	int need_to_read = std::min(_ram_size, left_elements_in_input);
	for (int i=0; i < need_to_read; i++) {
		_ram_vector[i] = _input->readUp();
	}
	_ram_count_elements = need_to_read;
}


void Solution::sortRam() {
	std::sort(begin(_ram_vector), begin(_ram_vector) + _ram_count_elements);
}


void Solution::printRam() {
	for (int i=0; i<_ram_count_elements; i++) {
		std::cout << _ram_vector[i] << " ";
	}
	std::cout << std::endl;
}

void Solution::writeRamToTape(BaseTape<int>* tape) {
	for (int i=0; i<_ram_count_elements; i++) {
		tape->write(_ram_vector[i]);
		tape->moveTape(1);
	}
}

/*
void Solution::inputData(BaseTape<int>* input, BaseTape<int>* temp1, BaseTape<int>* temp2) {
	std::vector<int> ram_vector(_k);
	for (int i=0; i < input->getSize(); ++i) {
		ram_vector[i % _k] = input->readUp();
		if (i % _k == 0) {
			std::sort(ram_vector.begin(), ram_vector.end());
			for (auto el=ram_vector.begin(); el<ram_vector.end(); el++) {
				temp1->write(*el);
				temp1->moveTape(1);
			}
		}
	}
	 // TODO delete this
	for (auto el=ram_vector.begin(); el<ram_vector.end(); el++) {
		std::cout << temp1->readDown() << " ";
	}
	std::cout << std::endl;
}
*/
