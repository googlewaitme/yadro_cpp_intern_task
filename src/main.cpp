#include <iostream>
#include <ctime>

#include "array_tape.h"
#include "solution.h"


int random(int start, int end);

void printTapeOnScreen(BaseTape<int>* tape);


int main() {
    std::srand(std::time(nullptr)); 
	int n = 85, ram_size = 10;
	std::vector<int> test_data;
	for (int i = 0; i < n; i++) {
		test_data.push_back(random(0, 100));
		std::cout << test_data[i] << " ";
		if (i > 0 && i % ram_size == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	BaseTape<int>* input = new ArrayTape<int>(test_data);

	BaseTape<int>* output = new ArrayTape<int>(std::vector<int> (n, 0));
	BaseTape<int>* temp1 = new ArrayTape<int>(std::vector<int> (input->getSize()));
	BaseTape<int>* temp2 = new ArrayTape<int>(std::vector<int> (input->getSize()));

	std::cout << "ram_size=" << ram_size << std::endl;
	Solution sol = Solution(ram_size, input, output, temp1, temp2);
	sol.sortTape();
	
	

	std::cout << "temp1" << std::endl;
	printTapeOnScreen(temp1);

	std::cout << "temp2" << std::endl;
	printTapeOnScreen(temp2);

	delete input;
	delete output;
	delete temp1;
	delete temp2;
	return 0;
}


int random(int start, int end) {
	int random = start + rand() % (end - start);
	return random;
}

void printTapeOnScreen(BaseTape<int>* tape) {
	int tape_pos = tape->getTapePosition();
	tape->moveTape(-tape_pos);
	for (int i=0; i < tape_pos; i++) {
		std::cout << tape->readUp() << " ";
	}
	std::cout << std::endl;
}
