#pragma once 

#include "../AstNode.h"

class VariableName : public AstNode {
public:

	void setName(std::string n) {
		name = n;
	}

	virtual Type getType() {
		return AstNode::Type::VariableName;
	}

	std::string name;

	~VariableName() {

	}

};