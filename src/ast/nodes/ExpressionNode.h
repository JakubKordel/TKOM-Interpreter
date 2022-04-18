#pragma once 

#include "../AstNode.h"

#include "../../EnumClasses/OperatorType.h"
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




class ExpressionNode : public AstNode {
public:
	void addOperand(Evaluable node) {
		this->operands.push_back(node);
	}

	void addOperator(OperatorType op) {
		this->operators.push_back(op);
	}

	virtual AstNode::Type getType() {
		return AstNode::Type::ExpressionNode;
	}

	std::vector<OperatorType> operators;
	std::vector<Evaluable> operands;

	~ExpressionNode();
};