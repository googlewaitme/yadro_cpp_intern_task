#include <iostream>
#include <ctime>
#include "array_tape.h"
#include "solution.h"


int random(int start, int end) {
	int random = start + rand() % (end - start);
	return random;
}

int main() {
    std::srand(std::time(nullptr)); 
	int n = 100, k = 10;
	std::vector<int> test_data;
	for (int i = 0; i < n; i++) {
		test_data.push_back(random(0, 100));
		std::cout << test_data[i] << " ";
	}
	std::cout << std::endl;

	BaseTape<int>* input = new ArrayTape(test_data);

	BaseTape<int>* output = new ArrayTape(std::vector<int> (n, 0));

	Solution sol = Solution(k);
	sol.sortTape(input, output);

	int out_pos = output->getTapePosition();
	output->moveTape(out_pos);

	for (int i; i<output->getSize(); i++) {
		std::cout << output->readUp() << " ";
	}

	delete input;
	delete output;
	return 0;
}
