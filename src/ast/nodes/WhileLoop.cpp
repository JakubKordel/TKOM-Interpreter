#include "WhileLoop.h"


WhileLoop::~WhileLoop() {
	std::visit([](auto a) { delete a; }, condition);
	delete block;
}