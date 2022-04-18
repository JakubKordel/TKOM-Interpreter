#include "IfStatement.h"

IfStatement::~IfStatement() {
	std::visit([](auto arg) {delete arg; }, condition);
	if (trueBlock) {
		delete trueBlock;
	}
	if (falseBlock) {
		delete falseBlock;
	}
}