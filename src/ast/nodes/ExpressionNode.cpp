#include "ExpressionNode.h"

ExpressionNode::~ExpressionNode() {
	for (auto it = operands.begin(); it != operands.end(); ++it) {
		std::visit([](auto a) { delete a; }, *it);
	}
}