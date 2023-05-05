#include "solution.h"
#include "base_tape.h"
#include "array_tape.h"
#include <vector>
#include <iostream>
#include <algorithm>


Solution::Solution(int number_integeres_fit_in_RAM) {
	// k - число integer, которые помещаются в оперативку.
	// TODO rename me
	int _k = number_integeres_fit_in_RAM;
}
void Solution::sortTape(BaseTape<int>* input, BaseTape<int>* output) {
	//
	// Временные ленты - передаются или создаются на входе
	// Пока пусть создаются, дальше придумаем что-нибудь
	BaseTape<int>* temp_tape_1 = new ArrayTape(std::vector<int> (input->getSize()));
	BaseTape<int>* temp_tape_2 = new ArrayTape(std::vector<int> (input->getSize()));	
	// Сортируем по K чисел на временные ленты
	inputData(input, temp_tape_1, temp_tape_2);
	// while( not sorted ):
	//    merge(TempTape1, TempTape2, output);
	//    sorted = split(output, TempTape1, TempTape2);
}


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
