#include "Execution.h"
#include "../Interpreter.h"

#include "Evaluation.h"


void exec(Executable executable, Interpreter * interpreter){
	std::visit(overload{

		[&interpreter](WhileLoop* obj) {
		Value condVal;
		condVal = eval(obj->condition, interpreter);
		while (!interpreter->functionContextStack.top().ret && std::get<bool>(condVal)) {
			exec(obj->block, interpreter);
			condVal = eval(obj->condition, interpreter);
		}

	},

		[&interpreter](IfStatement* obj) {
			bool cond;
			Value condVal = cond;
			condVal = eval(obj->condition, interpreter);
			if (std::get<bool>(condVal)) {
				exec(obj->trueBlock, interpreter);
			}
			else if (obj->falseBlock != nullptr) {
				exec(obj->falseBlock, interpreter);
			}

	},

		[&interpreter](Block* obj) {
			interpreter->functionContextStack.top().pushNewSubContext();
			for (Executable & instr : obj->instructions) {
				if (interpreter->functionContextStack.top().ret) {
					break;
				}
				exec(instr, interpreter);
			}
			interpreter->functionContextStack.top().popSubContext();

	},
		[&interpreter](StartBlock* obj) {
			for (auto squere : obj->declaredSqueres) {
				if (interpreter->objs.objExists(squere.objName))
					interpreter->map.place(squere.objName, squere.x, squere.y);
				else {
					throw std::invalid_argument("Object " + squere.objName + " not defined!");
				}
			}
	},

		[&interpreter](Language* obj) {
			for (auto def : obj->definitions) {
				exec(def, interpreter);
			}
			
	},	[&interpreter](ReturnStatement* obj) {
			interpreter->functionContextStack.top().retValue = eval(obj->returnValue, interpreter);
			interpreter->functionContextStack.top().ret = true;

	},	[&interpreter](FunctionCall* obj) {
			eval(obj, interpreter);

	},	[&interpreter](ValueAssignment* obj) {
			interpreter->functionContextStack.top().assign(obj->variableName, eval(obj->variableValue, interpreter));
	},

		[&interpreter](DefObject* obj) {
			interpreter->objs.insert(obj->objName);
	},

		[&interpreter](DefFunction* obj) {
			if (interpreter->functions.getFunctionDefinition(obj->functionName)) {
				throw std::invalid_argument("Function named " + obj->functionName + " already defined");
			}
			else if (interpreter->isBuildedInFunction(obj->functionName)) {
				throw std::invalid_argument("User defined function can't be named: " + obj->functionName);
			}
			else if (!obj->allParametersNamesDifferent()) {
				throw std::invalid_argument("All function parameters must have different names");
			}

			interpreter->functions.insert(obj->functionName, obj);
	},

		[&interpreter](DefGameParameter* obj) {
			if (obj->parameterName == "players") {
				if (obj->getValueType() == DefGameParameter::ValueType::Integer) {
					interpreter->playersNum = obj->intValue;
				}
				else {
					throw std::invalid_argument("Value of players parameter is not correctly defined");
				}
			} 
			else if (obj->parameterName == "name") {
				if (obj->getValueType() == DefGameParameter::ValueType::Word) {
					interpreter->gameName = obj->wordValue;
				}
				else {
					throw std::invalid_argument("Value of name parameter is not correctly defined");
				}
			}
			else if (obj->parameterName == "size") {
				if (obj->getValueType() == DefGameParameter::ValueType::Pair) {
					interpreter->map.initialize(obj->pairValue.first, obj->pairValue.second);
				}
				else {
					throw std::invalid_argument("Value of size parameter is not correctly defined");
				}
			}


	},	[&interpreter](LocalVariableDeclaration* obj) {
			if (!interpreter->objs.objExists(obj->variableName)) {
				if (!interpreter->functionContextStack.top().variableExists(obj->variableName)) {
					interpreter->functionContextStack.top().contexts.back().variables.insert(std::pair<std::string, Value>(obj->variableName, eval(obj->variableValue, interpreter)));
				}
				else {
					throw std::invalid_argument("Variable named " + obj->variableName + " already declared");
				}
			}
			else {
				throw std::invalid_argument("Local variable can't be named like defined object!");
			}
	}
		}, executable);
}
