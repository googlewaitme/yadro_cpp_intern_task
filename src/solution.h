#pragma once
#include "base_tape.h"
#include <vector>


class Solution {
private:
	// TODO rename this
	// k - count integer can fit in RAM
	
	int _ram_size;
	int _ram_count_elements;
	std::vector<int> _ram_vector;

	BaseTape<int>* _input;
	BaseTape<int>* _output;

	int _input_size;

	BaseTape<int>* _temp1;
	BaseTape<int>* _temp2;
	BaseTape<int>* _temp_tape;
	int _current_temp_tape;


	void readInRam();
	void sortRam();
	void printRam();
	void writeRamToTape(BaseTape<int>* tape);

	void mergeTapes();
	bool splitOutputToTapes();
	void changeTempTape();
public:
	Solution(
		int count_integers_fit_in_ram,
		BaseTape<int>* input,
		BaseTape<int>* output,
		BaseTape<int>* temp1,
		BaseTape<int>* temp2
	);

	void sortTape();

	void inputData();
};
