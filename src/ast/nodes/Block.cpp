#include "Block.h"

Block::~Block() {
	for (auto it = instructions.begin(); it != instructions.end(); ++it) {
		std::visit([](auto a) { delete a; }, *it);
	}
}