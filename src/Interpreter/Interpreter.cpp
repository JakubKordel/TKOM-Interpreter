#include "Interpreter.h"
#include <iostream>

typedef std::variant<PlaceOperation, ClearOperation> Operation;

Interpreter::Interpreter() {
	objs.insert("empty");
	initializeBuildedInFunctionality();
}

Interpreter::Interpreter(Language * lang){
	initializeBuildedInFunctionality();
	objs.insert("empty");
	load(lang);
}

void Interpreter::load(Language * lang){
	exec(lang, this);
}

void Interpreter::run(){

	while (!gameFinished) {
		std::cout << std::endl << gameName << std::endl;
		std::cout << "###########################################################" << std::endl << std::endl;
		map.print();
		std::cout << std::endl << std::endl << "###########################################################";
		operations.clear();
		while (!inputOperations());
		FunctionCall moveCheck;
		moveCheck.setName("isMoveLegal");
		if (std::get<bool>(eval(&moveCheck, this))) {
			updateMap();
			++onTurn;
			if (onTurn == playersNum) {
				onTurn = 0;
			}
		}
		else {
			std::cout << std::endl << "Move was illegal" << std::endl << std::endl;
		}
		FunctionCall endCheck;
		endCheck.setName("end");
		if (std::get<bool>(eval(&endCheck, this))) {
			printEndMsg();
			gameFinished = true;
		}

	}
}

void Interpreter::initializeBuildedInFunctionality() {
	buildedInFunctions.push_back("setWinner");
	buildedInFunctions.push_back("operationsNum");
	buildedInFunctions.push_back("isPlaceOperation");
	buildedInFunctions.push_back("onTurn");

	acceptableTableObjectsNames.push_back("CurrentPosition");
	acceptableTableObjectsNames.push_back("OperationList");
}

bool Interpreter::isBuildedInFunction(std::string name) {
	for (auto buildedInName : buildedInFunctions) {
		if (buildedInName == name) {
			return true;
		}
	}
	return false;
}

bool Interpreter::isAcceptableTableObjName(std::string name) {
	for (auto acceptable : acceptableTableObjectsNames) {
		if (acceptable == name) {
			return true;
		}
	}
	return false;
}

Value Interpreter::handleBuildedInFunction(FunctionCall * call) {
	if (call->functionName == "setWinner") {
		if (call->arguments.size() != 1) {
			throw std::invalid_argument("Builded in function setWinner accepts 1 argument");
		}
		Value val = eval(call->arguments[0], this);
		if (!std::holds_alternative<int>(val)) {
			throw std::invalid_argument("Argument of builded in function setWinner must be integer type");
		}
		int win = std::get<int>(val);
		if (win < 0 || win > playersNum) {
			throw std::invalid_argument("You can't set not existing player as a winner");
		}
		winner = win;
		return 0;
	}
	else if (call->functionName == "operationsNum") {
		if (call->arguments.size() != 0) {
			throw std::invalid_argument("Builded in function operationsNum doesn't accept any arguments");
		}
		return (int)operations.size();
	}
	else if (call->functionName == "isPlaceOperation") {
		if (call->arguments.size() != 1) {
			throw std::invalid_argument("Builded in function isPlaceOperation accepts one argument");
		}
		Value val = eval(call->arguments[0], this);
		if (!std::holds_alternative<int>(val)) {
			throw std::invalid_argument("Argument of builded in function isPlaceOperation must be integer type");
		}
		int oper = std::get<int>(val);
		if (oper < 0 || oper >= operations.size()) {
			return false;
		}
		return std::holds_alternative<PlaceOperation>(operations[oper]);
	}
	else if (call->functionName == "onTurn") {
		if (call->arguments.size() != 0) {
			throw std::invalid_argument("Builded in function onTurn doesn't accept any arguments");
		}
		return onTurn;
	}
	else {
		throw std::invalid_argument("Builed in function named " + call->functionName + " does not exist");
	}
}

Value Interpreter::handleBracketsName(BracketsName * obj) {

	if (obj->name == "CurrentPosition") {
		if (obj->bracketsValues.size() != 2) {
			throw std::invalid_argument("Table object CurrentPosition must have two brackets");
		}
		Value x = eval(obj->bracketsValues[0], this);
		Value y = eval(obj->bracketsValues[1], this);
		if (!std::holds_alternative<int>(x) || !std::holds_alternative<int>(y)) {
			throw std::invalid_argument("CurrentPosition coordinates have to be integers! ");
		}
		ObjValue obj = map.getObject(std::get<int>(x), std::get<int>(y));
		return obj;
	}

	else if (obj->name == "OperationList") {
		if (obj->bracketsValues.size() != 2) {
			throw std::invalid_argument("Table object OperationList must have two brackets");
		}
		Value arg1 = eval(obj->bracketsValues[0], this);
		Value arg2 = eval(obj->bracketsValues[1], this);
		if (!std::holds_alternative<int>(arg1) || !std::holds_alternative<int>(arg2)) {
			throw std::invalid_argument("OperationList's values in brackets have to be integers! ");
		}
		int a1 = std::get<int>(arg1);
		int a2 = std::get<int>(arg2);
		if (a1 < 0 || a1 >= operations.size()) {
			throw std::invalid_argument("Asked about not existing operation");
		}

		if (std::holds_alternative<PlaceOperation>(operations[a1])) {
			PlaceOperation oper = std::get<PlaceOperation>(operations[a1]);
			if (a2 < 0 || a2 > 2) {
				throw std::invalid_argument("Asked about not existing operation's argument");
			}

			if (a2 == 0) {
				return oper.x;
			}
			else if (a2 == 1) {
				return oper.y;
			}
			else {
				return oper.obj;
			}

		}
		else {
			ClearOperation oper = std::get<ClearOperation>(operations[a1]);
			if (a2 < 0 || a2 > 1) {
				throw std::invalid_argument("Asked about not existing operation's argument");
			}
			if (a2 == 0) {
				return oper.x;
			}
			else {
				return oper.y;
			}
		}
	}
}

bool Interpreter::inputOperations(){
	std::cout << std::endl <<"Add PlaceOperation: press p" << std::endl;
	std::cout << "Add ClearOperation: press c" << std::endl;
	std::cout << "Finish move:	press any letter" << std::endl;
	char choice;
	std::cin >> choice;
	switch (choice) {
		case 'p':
			inputPlaceOperation();
			return false;
		case 'c':
			inputClearOperation();
			return false;
		default:
			return true;
	}
}

void Interpreter::updateMap(){
	for (auto oper : operations) {
		if (std::holds_alternative<ClearOperation>(oper)) {
			ClearOperation clearOp = std::get<ClearOperation>(oper);
			map.clear(clearOp.x, clearOp.y);
		}
		else {
			PlaceOperation placeOp = std::get<PlaceOperation>(oper);
			map.place(placeOp.obj, placeOp.x, placeOp.y);
		}
	}
}

void Interpreter::printEndMsg(){
	std::cout << "###########################################################" << std::endl << std::endl;
	map.print();
	std::cout << std::endl << std::endl << "###########################################################";
	std::cout << std::endl;
	if (winner == -1) {
		std::cout << "DRAW";
	}
	if (winner == 0) {
		std::cout << "Player 1 Won";
	}
	if (winner == 1) {
		std::cout << "Player 2 Won";
	}


}

void Interpreter::inputPlaceOperation(){
	std::string obj;
	int x;
	int y;
	bool correct;
	do {
		std::cout << "Enter x: ";
		x = readInt();
		if (!(correct = (x >= 0 && x < map.getX()))) {
			std::cout << std::endl << "No such x coordinate in the map" << std::endl;
		}
	} while (!correct);
	do {
		std::cout << "Enter y: ";
		y = readInt();
		if (!(correct = (y >= 0 && y < map.getY()))) {
			std::cout << std::endl << "No such x coordinate in the map" << std::endl;
		}
	} while (!correct);
	std::cout << "Enter object: ";
	bool exists;
	do {
		std::cin >> obj;
		exists = objs.objExists(obj);
		if (!exists) {
			std::cout << "Object doesn't exist, enter existing: ";
		}
	} while (!exists);
	PlaceOperation oper;
	oper.obj = ObjValue(obj);
	oper.x = x;
	oper.y = y;
	operations.push_back(oper);
}

void Interpreter::inputClearOperation(){
	int x;
	int y;
	bool correct;
	do {
		std::cout << "Enter x: ";
		x = readInt();
		if (!(correct = (x >= 0 && x < map.getX()))) {
			std::cout << std::endl << "No such x coordinate in the map" << std::endl;
		}
	} while (!correct);
	do {
		std::cout << "Enter y: ";
		y = readInt();
		if (!(correct = (y >= 0 && y < map.getY()))) {
			std::cout << std::endl << "No such x coordinate in the map" << std::endl;
		}
	} while (!correct);

	ClearOperation oper;
	oper.x = x;
	oper.y = y;
	operations.push_back(oper);
}

int Interpreter::readInt() {
	int i;
	while (true) {
		std::cin >> i;
		if (!std::cin) {
			std::cout << "Enter integer: " << std::endl;
			std::cin.clear();
			continue;
		}
		else break;
	}
	return i;
}

void GameMap::initialize(int x_, int y_) {
	x = x_;
	y = y_;
	initialized = true;
	map = new ObjValue *[x];
	for (int i = 0; i < x; ++i)
		map[i] = new ObjValue[y];
}

void GameMap::clear(int x, int y) {
	if (initialized) {
		if (x < this->x && x >= 0 && y >= 0 && y < this->y) {
			map[x][y].value = "empty";
		}
		else {
			throw std::invalid_argument("Invalid map coordinates: x:" + std::to_string(x) + "y: " + std::to_string(y) + "!");
		}

	}
	else {
		throw std::invalid_argument("Map size is not initialized yet, define map size");
	}

}

void GameMap::place(ObjValue obj, int x, int y) {
	if (initialized) {
		if (x < this->x && x >= 0 && y >= 0 && y < this->y) {
			map[x][y].value = obj.value;
		}
		else {
			throw std::invalid_argument("Invalid map coordinates: x:" + std::to_string(x) + "y: " + std::to_string(y) + "!");
		}

	}
	else {
		throw std::invalid_argument("Map size is not initialized yet, define map size");
	}
}

ObjValue GameMap::getObject(int x, int y) {
	if (initialized) {
		if (x < this->x && x >= 0 && y >= 0 && y < this->y) {
			return map[x][y];
		}
		else {
			throw std::invalid_argument("Invalid map coordinates: x:" + std::to_string(x) + "y: " + std::to_string(y) + "!");
		}
	}
	else {
		throw std::invalid_argument("Map size is not initialized yet, define map size");
	}
}

int GameMap::getX() {
	if (initialized) {
		return x;
	}
	else {
		throw std::invalid_argument("Map size is not initialized yet, define map size");
	}
}

int GameMap::getY() {
	if (initialized) {
		return y;
	}
	else {
		throw std::invalid_argument("Map size is not initialized yet, define map size");
	}
}

void GameMap::print() {
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			std::cout << getObject(j, i).value + "\t";
		}
		std::cout << "\n";
	}
}

GameMap::~GameMap() {
	for (int i = 0; i < x; ++i) {
		delete [] map[i];
	}
	delete [] map;
}

void Context::insertNewVariable(std::string name, Value val) {
	variables.insert(std::pair<std::string, Value>(name, val));
}

void FunctionContext::pushNewSubContext() {
	Context context;
	contexts.push_back(context);
}

void FunctionContext::popSubContext() {
	contexts.pop_back();
}

void FunctionContext::assign(std::string variableName, Value newVal) {
	bool flag = false;
	for (Context & context : contexts) {
		auto it = context.variables.find(variableName);
		if (it != context.variables.end()) {
			it->second = newVal;
			flag = true;
		}
	}
	if (!flag) {
		throw std::invalid_argument("Variable name " + variableName + "not resolved!");
	}
}

Value FunctionContext::getVariableValue(std::string variableName) {
	for (Context & context : contexts) {
		auto it = context.variables.find(variableName);
		if (it != context.variables.end()) {
			return it->second;
		}
	}
	throw std::invalid_argument("Variable name " + variableName + "not resolved!");
}

bool FunctionContext::variableExists(std::string variableName) {
	for (Context & context : contexts) {
		auto it = context.variables.find(variableName);
		if (it != context.variables.end()) {
			return true;
		}
	}
	return false;
}

void FunctionContext::insertNewVariable(std::string name, Value val) {
	contexts.back().insertNewVariable(name, val);
}

void ObjDefinitons::insert(std::string obj) {
	objsList.push_back(obj);
}

bool ObjDefinitons::objExists(std::string objName) {
	for (auto obj : objsList) {
		if (obj == objName) {
			return true;
		}
	}
	return false;
}

void FunctionsDefinitions::insert(std::string name, DefFunction * fun) {
	functionsDefinitions.insert(std::pair<std::string, DefFunction*>(name, fun));
}

DefFunction * FunctionsDefinitions::getFunctionDefinition(std::string name, bool mustExist) {
	if (functionsDefinitions.count(name) == 0) {
		if (mustExist) {
			throw std::invalid_argument("No function called " + name);
		}
		else {
			return nullptr;
		}
	}
	return functionsDefinitions[name];
}
