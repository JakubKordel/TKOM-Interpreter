#include "ReturnStatement.h"


ReturnStatement::~ReturnStatement() {
	std::visit([](auto a) { delete a; }, returnValue);
}