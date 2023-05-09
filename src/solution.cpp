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
	std::cout << "t1pos, t2pos: " << _temp1->getTapePosition();
	std::cout << " " << _temp2->getTapePosition() << std::endl;


	_temp1 -> moveTape(-1);
	_temp2 -> moveTape(-1);
	int temp1_el = _temp1->readDown(),
		temp2_el = _temp2->readDown();
	int temp1_pos = _temp1->getTapePosition(),
		temp2_pos = _temp2->getTapePosition();
	while (temp1_pos > 0 and temp2_pos > 0) {
		if (temp1_el > temp2_el) {
			_output->write(temp1_el);
			temp1_el = _temp1->readDown();	
		} else {
			_output->write(temp2_el);
			temp2_el = _temp2->readDown();	
		}
		_output->moveTape(1);
		temp1_pos = _temp1->getTapePosition(),
		temp2_pos = _temp2->getTapePosition(),
		std::cout << "t1pos, t2pos: " << temp1_pos <<  " " << temp2_pos << std::endl;
		std::cout << "t1, t2: " << temp1_el << " " << temp2_el << std::endl;
	}

	// Здесь => потому у нас в прошлом цикле в кэш мы считали переменную. 
	while (temp1_pos >= 0) {
		_output->write(temp1_el);
		_output->moveTape(1);
		if (temp1_pos > 0)
			temp1_el = _temp1->readDown();
		else
			break;
		temp1_pos = _temp1->getTapePosition();
		std::cout << "t1, t1pos: " << temp1_el << " " << temp1_pos << std::endl;
	}

	while (temp2_pos >= 0) {
		_output->write(temp2_el);
		_output->moveTape(1);
		if (temp2_pos > 0)
			temp2_el = _temp2->readDown();	
		else
			break;
		temp2_pos = _temp2->getTapePosition();
		std::cout << "t2, t2pos: " << temp2_el << " " << temp2_pos << std::endl;
	}

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

	// TODO how calculate current_element and solve this problem
	int last_element, current_element;
	bool sorted = true;
	for (int i=0; i < _output->getSize(); i++) {
		last_element = current_element;
		current_element = _output->readDown();

		if (last_element > current_element) {
			changeTempTape();
			sorted = false;
		}
		_temp_tape->write(current_element);
		std::cout << _temp_tape->getTapePosition() << std::endl;
		_temp_tape->moveTape(1);
		std::cout << "tape_number, el: " << _current_temp_tape << " "; 
		std::cout << current_element << std::endl;
	}

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

