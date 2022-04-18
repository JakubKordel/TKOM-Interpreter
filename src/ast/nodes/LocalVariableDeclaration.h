#pragma once 

#include "../AstNode.h"
#include "../../EnumClasses/VariableType.h"

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

class LocalVariableDeclaration : public AstNode {
public:

	void setName(const std::string& name){
		variableName = name;
	}

	void setValue(Evaluable value){
		variableValue = value;
	}

	void setType(const VariableType type) {
		variableType = type;
	}

	virtual AstNode::Type getType(){
		return AstNode::Type::LocalVariableDeclaration;
	}

	std::string variableName;
	VariableType variableType;
	Evaluable variableValue;

	~LocalVariableDeclaration();
};