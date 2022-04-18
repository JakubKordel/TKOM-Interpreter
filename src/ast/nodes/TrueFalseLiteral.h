#pragma once 

#include "../AstNode.h"

class TrueFalseLiteral : public AstNode {
public:

	void setValue(bool val) {
		value = val;
	}

	virtual Type getType() {
		return AstNode::Type::TrueFalseLiteral;
	}

	bool value;

	~TrueFalseLiteral() {

	}
};