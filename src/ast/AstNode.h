#pragma once

#include <memory>

class AstNode{

public:
	enum class Type {
		Assignable,
		Block,
		DefFunction,
		DefGameParameter,
		DefObject,
		DefStart,
		ExpressionNode,
		FunctionCall,
		WhileLoop,
		IfStatement,
		Language,
		LocalVariableDeclaration,
		ReturnStatement,
		SquereDefinition,
		StartBlock,
		ValueAssignment,
		FloatLiteral,
		IntLiteral,
		VariableName,
		BracketsName,
		TrueFalseLiteral
	};

	virtual Type getType() = 0;
};

typedef std::unique_ptr<AstNode> AstNodePtr;


#include "nodes/Block.h"
#include "nodes/DefFunction.h"
#include "nodes/DefGameParameter.h"
#include "nodes/DefObject.h"
#include "nodes/ExpressionNode.h"
#include "nodes/FunctionCall.h"
#include "nodes/WhileLoop.h"
#include "nodes/IfStatement.h"
#include "nodes/Language.h"
#include "nodes/LocalVariableDeclaration.h"
#include "nodes/ReturnStatement.h"
#include "nodes/StartBlock.h"
#include "nodes/ValueAssignment.h"
#include "nodes/FloatLiteral.h"
#include "nodes/IntLiteral.h"
#include "nodes/VariableName.h"
#include "nodes/BracketsName.h"
#include "nodes/VariableName.h"
#include "nodes/TrueFalseLiteral.h"
#include <vector>



