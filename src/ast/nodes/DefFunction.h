#pragma once 

#include "../AstNode.h"
#include "../../EnumClasses/VariableType.h"

#include <string>
#include <variant>
#include <vector>

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
class Block;


typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;


class DefFunction : public AstNode {


	public:

	std::string functionName;
	std::vector<std::pair<VariableType, std::string>> parameters;
	VariableType returnType;

	Block * functionBlock;
	
	void setFunctionName(std::string name) {
		functionName = name;
	}

	void setParameters(std::vector<std::pair<VariableType, std::string>> p) {
		parameters = p;
	}


	void setReturnType(VariableType type) {
		returnType = type;
	}

	void setBlock(Block * block) {
		functionBlock = block; 
	}

	virtual Type getType() {
		return AstNode::Type::DefFunction;
	}

	bool allParametersNamesDifferent() {
		for (auto it1 = parameters.begin(); it1 != parameters.end(); ++it1) {
			for (auto it2 = it1 + 1; it2 != parameters.end(); ++it2) {
				if (it1->second == it2->second) {
					return false;
				}
			}
		}
		return true;
	}

	~DefFunction();

};