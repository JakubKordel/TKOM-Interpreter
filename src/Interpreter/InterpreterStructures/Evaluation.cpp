#include "Evaluation.h"

#include "../Interpreter.h"

#include "../../EnumClasses/OperatorType.h"

#include "../../EnumClasses/VariableType.h"

#include "Execution.h"

#include <iostream>

std::string getValueName(Value value) {
	std::string str;

	std::visit(overload{
		[&str](VoidValue val) {
		str = "void";
	},
		[&str](ObjValue val) {
		str = "obj";
	},
		[&str](bool val) {
		str = "bool";
	},
		[&str](int val) {
		str = "int";
	},
		[&str](float val) {
		str = "float";
	}
		}, value);

	return str;
}

VariableType getType(Value value) {
	VariableType varType;

	std::visit(overload{
		[&varType](VoidValue val) {
			varType = VariableType::Void;
	},
		[&varType](ObjValue val) {
			varType = VariableType::Obj;
	},
		[&varType](bool val) {
			varType = VariableType::Bool;
	},
		[&varType](int val) {
			varType = VariableType::Int;
	},
		[&varType](float val) {
			varType = VariableType::Float;
	}
		}, value);

	return varType;
}

bool equalityCheck(Value left, Value right) {
	bool param;
	std::visit(overload{
		[&param](ObjValue l, ObjValue r) {
		param = (l == r);
	},
		[&param](bool l, bool r) {
		param = (l == r);
	},
		[&param](int l, int r) {
		param = (l == r);
	},
		[&param](float l, float r) {
		param = (l == r);
	},
		[&param](float l, int r) {
		param = (l == (float)r);
	},
		[&param](int l, float r) {
		param = ((float)l == r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't compare values of types " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

bool lessCheck(Value left, Value right) {
	bool param;
	std::visit(overload{
		[&param](bool l, bool r) {
		param = (l < r);
	},
		[&param](int l, int r) {
		param = (l < r);
	},
		[&param](float l, float r) {
		param = (l < r);
	},
		[&param](float l, int r) {
		param = (l < (float)r);
	},
		[&param](int l, float r) {
		param = ((float)l < r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("No precendence relation defined for " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

bool greaterCheck(Value left, Value right) {
	return lessCheck(right, left);
}

bool lessEqualCheck(Value left, Value right) {
	return lessCheck(left, right) || equalityCheck(left, right);
}

bool greaterEqualCheck(Value left, Value right) {
	return greaterCheck(left, right) || equalityCheck(left, right);
}

bool notEqualCheck(Value left, Value right) {
	return !equalityCheck(left, right);
}

bool andEvaluate(Value left, Value right){
	bool param;
	std::visit(overload{
		[&param](bool l, bool r) {
		param = (l && r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't perform and operation beetween " + getValueName(l) + "and " + getValueName(r) + " arguments.");
	}
		}, left, right);
	return param;
}

bool orEvaluate(Value left, Value right){
	bool param;
	std::visit(overload{
		[&param](bool l, bool r) {
		param = (l || r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't perform or operation beetween " + getValueName(l) + "and " + getValueName(r) + " arguments.");
	}
		}, left, right);
	return param;
}

Value add(Value left, Value right){
	Value param;
	std::visit(overload{
		[&param](int l, int r) {
		param = (l + r);
	},
		[&param](float l, float r) {
		param = (l + r);
	},
		[&param](float l, int r) {
		param = (l  + (float)r);
	},
		[&param](int l, float r) {
		param = ((float)l + r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't add values of types " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

Value substract(Value left, Value right){
	Value param;
	std::visit(overload{
		[&param](int l, int r) {
		param = (l - r);
	},
		[&param](float l, float r) {
		param = (l - r);
	},
		[&param](float l, int r) {
		param = (l - (float)r);
	},
		[&param](int l, float r) {
		param = ((float)l - r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't substract values of types " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

Value multiply(Value left, Value right){
	Value param;
	std::visit(overload{
		[&param](int l, int r) {
		param = (l * r);
	},
		[&param](float l, float r) {
		param = (l * r);
	},
		[&param](float l, int r) {
		param = (l * (float)r);
	},
		[&param](int l, float r) {
		param = ((float)l * r);
	},
		[&param](auto l, auto r) {
		throw std::invalid_argument("Can't multiply values of types " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

Value divide(Value left, Value right){
	Value param;
	std::visit(overload{
		[&param](int l, int r) {
			param = (l / r);
	},
		[&param](float l, float r) {
			param = (l / r);
	},
		[&param](float l, int r) {
			param = (l / (float)r);
	},
		[&param](int l, float r) {
			param = ((float)l / r);
	},
		[&param](auto l, auto r) {
			throw std::invalid_argument("Can't divide values of types " + getValueName(l) + "and " + getValueName(r));
	}
		}, left, right);
	return param;
}

Value negate(Value value){
	Value neg;
	std::visit(overload{
		[&neg](bool val) {
		neg = !val;
	},
		[&neg](int val) {
		neg = -val;
	},
		[&neg](float val) {
		neg = -val;
	},
		[&neg](auto val) {
		throw std::invalid_argument("Can't negate value of type " + getValueName(val));
	}
		}, value);
	return neg;
}

void assign(Value & left, Value right){
	std::visit(overload{
		[](int & l, int & r) {
			l = r;
	},
		[](float & l, float & r) {
			l = r;
	},
		[](float & l, int & r) {
			l = r;
	},
		[](int & l, float & r) {
			l = r;
	},
		[](bool & l, int & r) {
			l = (bool)r;
	},
		[](auto l, auto r) {
			throw std::invalid_argument("Can't assign value of type " + getValueName(r) + "to type " + getValueName(l));
	}
		}, left, right);
}

Value eval(Evaluable evaluable, Interpreter * interpreter){
	std::pair<Interpreter*, Value> params;
	params.first = interpreter;

	std::visit(overload{
		[&params](ExpressionNode* expr) {
			if (expr->operands.size() == 1 && expr->operators.size() == 1) {
				if (expr->operators[0] == OperatorType::Substract || expr->operators[0] == OperatorType::Negation) {
					params.second = negate( eval(expr->operands[0], params.first));
				}
				else {
					throw std::invalid_argument("Ast tree made not properly!");
				}
			}
			else if (expr->operands.size() == expr->operators.size() + 1 ) {
				int i = 0;
				Value lhs = eval(expr->operands[i], params.first);
				for (auto oper : expr->operators) {
					++i;
					switch (oper) {
						case OperatorType::Equal: 
							lhs = equalityCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::NotEqual:
							lhs = notEqualCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Add:
							lhs = add(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Substract:
							lhs = substract(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Divide:
							lhs = divide(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Multiply:
							lhs = multiply(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Less:
							lhs = lessCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Greater:
							lhs = greaterCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::LessEqual:
							lhs = lessEqualCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::GreaterEqual:
							lhs = greaterEqualCheck(lhs, eval(expr->operands[i], params.first));
							break;
						case OperatorType::Or:
							if ((std::holds_alternative<bool>(lhs) && !std::get<bool>(lhs))||(!std::holds_alternative<bool>(lhs))) {
								lhs = orEvaluate(lhs, eval(expr->operands[i], params.first));
							}
							break;
						case OperatorType::And:
							if ((std::holds_alternative<bool>(lhs) && std::get<bool>(lhs)) || (!std::holds_alternative<bool>(lhs))) {
								lhs = andEvaluate(lhs, eval(expr->operands[i], params.first));
							}
							break;

					}
				}
				params.second = lhs;
			}
	},
		[&params](BracketsName* bracketsObj) {
			Interpreter * interpreter = params.first;
			params.second = interpreter->handleBracketsName(bracketsObj);
	},
		[&params](FloatLiteral* floatNumber) {
			params.second = floatNumber->value;
	},
		[&params](IntLiteral* intNumber) {
			params.second = intNumber->value;
	},
		[&params](VariableName* var) {
			if (params.first->objs.objExists(var->name)) {
				params.second = ObjValue(var->name);
			}
			else {
				params.second = params.first->functionContextStack.top().getVariableValue(var->name);
			}
	},	[&params](FunctionCall* obj) {
			Interpreter * interpreter = params.first;
			if (interpreter->isBuildedInFunction(obj->functionName)) {
				params.second = interpreter->handleBuildedInFunction(obj);
			}
			else {
				DefFunction * funDef = interpreter->functions.getFunctionDefinition(obj->functionName, true);
				if (obj->arguments.size() != funDef->parameters.size()) {
					throw std::invalid_argument("wrong arguments count in call of function " + obj->functionName);
				}
				FunctionContext funContext;
				funContext.pushNewSubContext();
				int i = 0;
				for (auto vars : funDef->parameters) {
					funContext.insertNewVariable(vars.second, eval(obj->arguments[i], interpreter));
					++i;
				}
				interpreter->functionContextStack.push(funContext);
				exec(funDef->functionBlock, interpreter);
				params.second = interpreter->functionContextStack.top().retValue;
				interpreter->functionContextStack.pop();
			}

	},	[&params](TrueFalseLiteral* booleanValue) {
			params.second = booleanValue->value;
	}
		}, evaluable);
	return params.second;
}
