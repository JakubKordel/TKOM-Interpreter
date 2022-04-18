#pragma once 

#include "../AstNode.h"

class DefObject : public AstNode {
public:
	std::string objName;

	DefObject(std::string name) {
		setName(name);
	}

	void setName(std::string name) {
		objName = name;
	}

	virtual AstNode::Type getType() {
		return AstNode::Type::DefObject;
	}

};