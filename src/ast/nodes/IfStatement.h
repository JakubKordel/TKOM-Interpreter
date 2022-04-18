#pragma once 

#include "../AstNode.h"

//#include "../../VariantsDefinitions/variantsDefinitons.h"

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


class IfStatement : public AstNode {

public:

	void setCondition(Evaluable con){
		condition = con;
	}

	void setTrueBlock(Block * block){
		trueBlock = block;
	}

	void setFalseBlock(Block * block){
		falseBlock = block;
	}

	virtual AstNode::Type getType(){
		return AstNode::Type::IfStatement;
	}

	Evaluable condition;

	Block * trueBlock = nullptr;

	Block * falseBlock = nullptr;

	~IfStatement();
	
};