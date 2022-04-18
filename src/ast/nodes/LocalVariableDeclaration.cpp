#include "LocalVariableDeclaration.h"

LocalVariableDeclaration::~LocalVariableDeclaration() {
	std::visit([](auto a) { delete a; }, variableValue);
}