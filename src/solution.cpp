#include "base_tape.h"
#include <vector>


Solution::Solution(int size_of_temp_tapes) {
	_size_of_temp_tapes = size_of_temp_tapes;
}
void Solution::sortTape(BaseTape<int> input, BaseTape<int> output) {
	// Временные ленты - передаются или создаются на входе
	// Пока пусть создаются, дальше придумаем что-нибудь
		
	// Сортируем по K на временные ленты
	//
	// while( not sorted ):
	//    merge(TempTape1, TempTape2, output);
	//    sorted = split(output, TempTape1, TempTape2);
}
