#pragma once 

#include "../AstNode.h"

class SquereDeclaration {
public:
	int x;
	int y;
	std::string objName;

	SquereDeclaration(int x, int y, std::string objName) {
		this->x = x;
		this->y = y;
		this->objName = objName;
	}
};

class StartBlock : public AstNode {

public:
	std::vector<SquereDeclaration> declaredSqueres;

	void addDeclaredSquere(SquereDeclaration squereDeclaration) {
		declaredSqueres.push_back(squereDeclaration);
	}

	void addDeclaredSquere(int x, int y, std::string objName) {
		declaredSqueres.push_back(SquereDeclaration(x,y, objName));
	}

	virtual AstNode::Type getType() {
		return AstNode::Type::StartBlock;
	}
};