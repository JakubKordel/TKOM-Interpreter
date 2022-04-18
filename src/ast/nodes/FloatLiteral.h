#pragma once 

#include "../AstNode.h"

class FloatLiteral : public AstNode {
public:

	void setValue(float val) {
		value = val;
	}

	virtual Type getType() {
		return AstNode::Type::FloatLiteral;
	}

	float value;

	~FloatLiteral();

};