#pragma once

#include "../../ast/AstNode.h"
#include "ObjValue.h"
#include "VoidValue.h"

#include <string>
#include <variant>

class Interpreter;

typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;

//template<class... Ts> struct overload : Ts... { using Ts::operator()...; };

typedef std::variant<VoidValue, ObjValue, bool, int, float> Value;

void exec(Executable executable, Interpreter * interpreter);