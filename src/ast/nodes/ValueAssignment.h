#pragma once 

#include "../AstNode.h"

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



class ValueAssignment : public AstNode {
public:
	void setVariableName(const std::string & name){
		variableName = name;
	}

	void setValue(Evaluable value){
		variableValue = value;
	}

	virtual Type getType(){
		return AstNode::Type::ValueAssignment;
	}

	std::string variableName;
	Evaluable variableValue;

	~ValueAssignment();
};