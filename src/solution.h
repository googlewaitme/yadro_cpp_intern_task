#pragma once
#include "base_tape.h"


class Solution {
private:
	int _size_of_temp_tapes;
public:
	Solution(int size_of_temp_tapes);

	void sortTape(BaseTape<int> input, BaseTape<int> output);
};
