#pragma once

#include "../Scanner/Scanner.h"
#include "../ast/AstNode.h"

#include "../Tokens/Token.h"

#include <vector>
#include <utility>
#include <string>
#include <map>
#include <stack>
#include <string>

#include <iostream>

#include "InterpreterStructures/Evaluation.h"
#include "InterpreterStructures/Execution.h"
#include "InterpreterStructures/VoidValue.h"
#include "InterpreterStructures/ObjValue.h"

class PlaceOperation;
class ClearOperation;

typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;
typedef std::variant<VoidValue, ObjValue, bool, int, float> Value;

typedef std::variant<PlaceOperation, ClearOperation> Operation;

class Context {
public:
	std::map<std::string, Value> variables;

	void insertNewVariable(std::string name, Value val);
};

class FunctionContext {
public:
	std::vector<Context> contexts;
	bool ret = false;
	Value retValue;
	void pushNewSubContext();
	void popSubContext();
	void assign(std::string variableName, Value newVal);
	Value getVariableValue(std::string variableName);
	bool variableExists(std::string variableName);
	void insertNewVariable(std::string name, Value val);
};

class ObjDefinitons {
public:
	std::vector<std::string> objsList;
	void insert(std::string obj);
	bool objExists(std::string objName);
};

class FunctionsDefinitions {
	std::map<std::string, DefFunction*> functionsDefinitions;
public:

	void insert(std::string name, DefFunction* fun);
	DefFunction * getFunctionDefinition(std::string name, bool mustExist = false);
};


class GameMap {
public:

	void initialize(int x_, int y_);
	void clear(int x, int y);
	void place(ObjValue obj, int x, int y);
	ObjValue getObject(int x, int y);
	int getX();
	int getY();
	void print();

	~GameMap();

private:

	bool initialized = false;
	int x;
	int y;
	ObjValue ** map = nullptr;

};

class PlaceOperation {
public:
	int x; 
	int y;
	ObjValue obj;
};

class ClearOperation {
public:
	int x;
	int y;
};


class Interpreter {
public:

	Interpreter();

	Interpreter(Language * lang);

	void load(Language * lang);

	FunctionsDefinitions functions;
	ObjDefinitons objs;
	std::stack<FunctionContext> functionContextStack;

	std::vector<Operation> operations;

	GameMap map;


	std::vector<std::string> buildedInFunctions;
	std::vector<std::string> acceptableTableObjectsNames;

	int playersNum;
	std::string gameName = "";
	void run();

	int winner = -1;

	int onTurn = 0;

	bool gameFinished = false;

	void initializeBuildedInFunctionality();

	bool isBuildedInFunction(std::string name);
	bool isAcceptableTableObjName(std::string name);

	Value handleBuildedInFunction(FunctionCall * call);

	Value handleBracketsName(BracketsName * obj);

	bool inputOperations();

	void updateMap();

	void printEndMsg();

	void inputPlaceOperation();

	void inputClearOperation();

	int readInt();
};