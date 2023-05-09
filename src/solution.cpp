#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>


#include "solution.h"
#include "base_tape.h"
#include "array_tape.h"


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

	// Нужно для массива временных лент
	_temp_tape = _temp1;
	_current_temp_tape = 0;
}


void Solution::sortTape() {
	// Сортируем по K чисел на временные ленты
	inputData();

	bool sorted = false;
	while (! sorted) {
		mergeTapes();
		sorted = splitOutputToTapes();
	}
	// TODO delete this
	std::cout << "\n\n answer \n\n";
	_output->print_array();
	std::cout << "\n\n";
}


void Solution::inputData() {
	int count_of_full_sets = _input_size / _ram_size;
	if (_input_size % _ram_size > 0)
		count_of_full_sets += 1;
	for (int i=0; i < count_of_full_sets; i++) {
		readInRam();
		sortRam();
		printRam();
		changeTempTape();
		writeRamToTape();
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

void Solution::writeRamToTape() {
	writeRamToTape(_temp_tape);
}


void Solution::mergeTapes() {
	/*
	Временные ленты состоят из набора отсортированных 
	отрезков. Нужно объединить их на выходной ленте
	для этого необходимо использовать подход с двумя 
	указателей.

	Головы временных лент находятся на последнем 
	элементе данных временных лент. Голова output
	Должен находится на нулевом элементе. 
	За работу функции головы временных лент уйдут в 
	нулевые элементы, а выходная лента будет указывать
	на последний элемент.
	 */
	std::cout << "Start merge" << std::endl;


	std::cout << "temp1" << std::endl;
	_temp1->print_array();
	std::cout << "temp2" << std::endl;
	_temp2->print_array();

	int len_temp1 = _temp1->getTapePosition(),
		len_temp2 = _temp2->getTapePosition();
	std::cout << "len(temp1), len(temp2): " << len_temp1 << " " << len_temp2 << std::endl;
	assert(len_temp1 + len_temp2 == _output->getSize());

	int in_memory1, in_memory2, to_write_in_output;
	if (len_temp1 > 0) {
		_temp1 -> moveTape(-1);
		in_memory1=_temp1->readDown();
	}
	if (len_temp2 > 0) {
		_temp2 -> moveTape(-1);
		in_memory2=_temp2->readDown();
	}

	std::cout << "start " << in_memory1 << " " << in_memory2 << std::endl;
	
	while (len_temp1 > 0 && len_temp2 > 0) {
		if (in_memory1 > in_memory2) {
			std::cout << "temp1" << " " << in_memory1 << std::endl;
			to_write_in_output = in_memory1;
			len_temp1--;
			if (len_temp1 > 1)
				in_memory1 = _temp1->readDown();
			else
				in_memory1 = _temp1->read();
		} else {
			std::cout << "temp2" << " " << in_memory2 << std::endl;
			to_write_in_output = in_memory2;
			len_temp2--;
			if (len_temp2 > 1)
				in_memory2 = _temp2->readDown();
			else
				in_memory2 = _temp2->read();
		}
		_output->write(to_write_in_output);
		_output->moveTape(1);
		std::cout << "Added in output: " << to_write_in_output << std::endl;
	}
	

	while (len_temp1 > 0) {
		_output->write(in_memory1);
		_output->moveTape(1);
		std::cout << "Added in output(last in temp1): " << in_memory1 << std::endl;
		len_temp1--;
		if (len_temp1 > 1)
			in_memory1 = _temp1->readDown();
		else 
			in_memory1 = _temp1->read();
	}

	while (len_temp2 > 0) {
		_output->write(in_memory2);
		_output->moveTape(1);
		std::cout << "Added in output(last in temp2): " << in_memory2 << std::endl;
		len_temp2--;
		if (len_temp2 > 1)
			in_memory2 = _temp2->readDown();
		else
			in_memory2 = _temp2->read();
	}

	std::cout << "output array:\n";
	_output->print_array();
	assert(_output->getTapePosition() == _output->getSize());		
	std::cout << "End merge" << std::endl;
}


bool Solution::splitOutputToTapes() {
	/*
	На момент запуска данной функции, выходная лента, 
	состоит из набора отсортированных участков. Нужно 
	разбить данные куски на временные ленты и объединять
	их на выходной ленте функцией merge. 

	После функции merge, времен.ленты стоят в начале, а 
	выходная лента стоит на последнем элементе. Мы их будем 
	двигать в обратном направлении относительно merge.
	У лент не будет пустых проходов, только нагруженные 
	полезной нагрузкой.

	Возвращаем ответ на вопрос: отсортирована ли выходная лента?
	*/
	std::cout << "start split" << std::endl;

	assert(_temp1->getTapePosition() == 0);
	assert(_temp2->getTapePosition() == 0);
	assert(_temp_tape->getTapePosition() == 0);
	assert(_output->getTapePosition() == _output->getSize());
	// Самое главное, чтобы в начале текущий элемент не был равен, предыдущему.
	// КОСТЫЛЬ!!!
	_output->moveTape(-1);
	int current_element = _output->readDown();
	int last_element = current_element-1;
	bool sorted = true;
	for (int i=0; i < _output->getSize(); i++) {
		if (last_element > current_element) {
			changeTempTape();
			sorted = false;
			std::cout << "array not sorted, change tape" << std::endl;
		}
		_temp_tape->write(current_element);
		_temp_tape->moveTape(1);
		std::cout << "tape_number, el: " << _current_temp_tape << " "; 
		std::cout << current_element << std::endl;
		last_element = current_element;
		if (i+2 < _output->getSize())
			current_element = _output->readDown();
		else
			current_element = _output->read();
	}

	assert(_temp1->getTapePosition() + _temp2->getTapePosition() == _output->getSize());
	std::cout << "output is sorted: " << sorted << std::endl;
	std::cout << "end split" << std::endl;
	return sorted;
}

void Solution::changeTempTape() {
	/*  Если переделывать решение на набор временных лент, 
	 *  то понадобится данная функция
	 *  */
	int count_of_tapes = 2;
	if (_current_temp_tape == 0) {
		_temp_tape = _temp1;
	} else {
		_temp_tape = _temp2;
	}
	_current_temp_tape = (_current_temp_tape + 1) % count_of_tapes;
}

