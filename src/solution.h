#pragma once
#include "base_tape.h"


class Solution {
private:
	// TODO rename this
	// k - count integer can fit in RAM
	int _k;
public:
	Solution(int count_integers_fit_in_ram);

	void sortTape(BaseTape<int>* input, BaseTape<int>* output);

	void inputData(BaseTape<int>* input, BaseTape<int>* temp1, BaseTape<int>* temp2);
};
