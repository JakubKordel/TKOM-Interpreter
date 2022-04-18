#include "ValueAssignment.h"

ValueAssignment::~ValueAssignment() {
	std::visit([](auto a) { delete a; }, variableValue);
}