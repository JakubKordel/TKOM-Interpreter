#pragma once 

#include "ObjValue.h"
#include "VoidValue.h"

#include <string>
#include <variant>

#include "../../ast/AstNode.h"

class Interpreter;

typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;

typedef std::variant<VoidValue, ObjValue, bool, int, float> Value;

std::string getValueName(Value value);

bool equalityCheck(Value left, Value right);

bool lessCheck(Value left, Value right);

bool greaterCheck(Value left, Value right);

bool lessEqualCheck(Value left, Value right);

bool greaterEqualCheck(Value left, Value right);

bool notEqualCheck(Value left, Value right);

bool andEvaluate(Value left, Value right);

bool orEvaluate(Value left, Value right);

Value add(Value left, Value right);

Value substract(Value left, Value right);

Value multiply(Value left, Value right);

Value divide(Value left, Value right);

Value negate(Value val);

void assign(Value & left, Value right);

Value eval(Evaluable evaluable, Interpreter * interpreter);

