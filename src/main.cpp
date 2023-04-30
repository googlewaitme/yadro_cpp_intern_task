#include <iostream>
#include "array_tape.h"
#include "solution.h"

int main() {
	ArrayTape<int> ms(std::vector<int> {1,2,3});
	std::cout << "Hello, world!" << std::endl;

	std::cout << ms.readUp() << " " << ms.readUp() << " " << ms.readDown();
	return 0;
}
