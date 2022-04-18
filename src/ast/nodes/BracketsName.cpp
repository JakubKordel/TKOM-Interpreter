#include "BracketsName.h"

BracketsName::~BracketsName() {
	for (auto it = bracketsValues.begin(); it != bracketsValues.end(); ++it) {
		std::visit([](auto a) { delete a; }, *it);
	}
}