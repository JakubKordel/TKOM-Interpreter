#pragma once 

#include "../AstNode.h"

#include "../../VariantsDefinitions/variantsDefinitons.h"

#include <vector>
#include <variant>
#include <string>

class WhileLoop;
class IfStatement;
class Block;
class StartBlock;
class Language;
class ReturnStatement;
class FunctionCall;
class ValueAssignment;
class DefObject;
class DefFunction;
class DefGameParameter;
class LocalVariableDeclaration;
class ExpressionNode;
class BracketsName;
class FloatLiteral;
class IntLiteral;
class VariableName;
class TrueFalseLiteral;

typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;


class BracketsName : public AstNode {
public:

	void setName(std::string n) {
		name = n;
	}

	void addValue(Evaluable value) {
		bracketsValues.push_back(value);
	}

	virtual Type getType() {
		return AstNode::Type::BracketsName;
	}

	std::string name;
	std::vector<Evaluable> bracketsValues;

	~BracketsName();

};