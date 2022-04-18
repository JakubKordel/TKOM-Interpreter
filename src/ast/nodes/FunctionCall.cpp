#include "FunctionCall.h"

FunctionCall::~FunctionCall() {
	for (auto it = arguments.begin(); it != arguments.end(); ++it) {
		std::visit([](auto a) { delete a; }, *it);
	}
}