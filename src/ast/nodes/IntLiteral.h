#pragma once 

#include "../AstNode.h"

class IntLiteral : public AstNode {
public:

	void setValue(int val) {
		value = val;
	}

	virtual Type getType() {
		return AstNode::Type::IntLiteral;
	}

	int value;

	~IntLiteral();

};