#define BOOST_TEST_MODULE InterpreterTests

#include <sstream>

#include <fstream>

#include <boost/test/included/unit_test.hpp>

#include <boost/test/unit_test.hpp>

#include "src/Scanner/Scanner.h"
#include "src/ast/AstNode.h"
#include "src/Parser/Parser.h"
#include "src/EnumClasses/OperatorType.h"
#include "src/EnumClasses/GameParameterType.h"
#include "src/EnumClasses/VariableType.h"
#include "src/VariantsDefinitions/variantsDefinitons.h"

#include <memory>
#include <cstdlib>
#include <variant>

#include "src/Interpreter/Interpreter.h"
#include "src/Interpreter/InterpreterStructures/ObjValue.h"
#include "src/Interpreter/InterpreterStructures/VoidValue.h"

typedef std::variant<VoidValue, ObjValue, bool, int, float> Value;


BOOST_AUTO_TEST_CASE(FunctionEvalTest) {
	std::string line1 = "define funTest(int number1, int number2){ return number1 + number2 * 5; }";
	std::string line2 = "funTest( 3 ,  2 );";
	std::istringstream in(line1 + line2);
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));
	parser.advance();

	Interpreter interpreter;

	DefFunction * funDef = parser.parseDefFunction();

	FunctionCall * functionCall = std::get<FunctionCall*>(parser.parseValueAssignmentOrFunctionCall());
	exec(funDef, &interpreter);
	Value result = eval(functionCall, &interpreter);

	BOOST_CHECK(std::holds_alternative<int>(result));
	BOOST_CHECK(std::get<int>(result) == 13);
	delete funDef;
	delete functionCall;
}


BOOST_AUTO_TEST_CASE(WhileTest) {

	std::string line1 = "define silnia(int number){												";
	std::string line2 = "		int i = 1;														";
	std::string line3 = "		int result = 1;													";
	std::string line4 = "		while(i <= number){												";
	std::string line5 = "			result = result * i;										";
	std::string line6 = "			i = i+1; 													";
	std::string line7 = "		}																";
	std::string line8 = "		return result; 													";
	std::string line9 = "}																		";
	std::string line10 = "silnia( 5 );															";


	std::istringstream in(line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8+ line9+ line10);
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));
	parser.advance();

	Interpreter interpreter;

	DefFunction * funDef = parser.parseDefFunction();

	FunctionCall * functionCall = std::get<FunctionCall*>(parser.parseValueAssignmentOrFunctionCall());

	exec(funDef, &interpreter);
	Value result = eval(functionCall, &interpreter);


	BOOST_CHECK(std::holds_alternative<int>(result));
	BOOST_CHECK(std::get<int>(result) == 120);
	delete funDef;
	delete functionCall;
}

BOOST_AUTO_TEST_CASE(RecursionAndIfTest) {

	std::string line1 = "define silnia(int number) -> int{												";
	std::string line2 = "		if (number == 0){												";
	std::string line3 = "			return 1;													";
	std::string line4 = "		} else {														";
	std::string line5 = "			return number*silnia(number - 1);							";
	std::string line6 = "		}																";
	std::string line7 = "}																		";
	std::string line8 = "silnia( 5 );															";


	std::istringstream in(line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8);
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));
	parser.advance();

	Interpreter interpreter;

	DefFunction * funDef = parser.parseDefFunction();

	FunctionCall * functionCall = std::get<FunctionCall*>(parser.parseValueAssignmentOrFunctionCall());

	exec(funDef, &interpreter);
	Value result = eval(functionCall, &interpreter);


	BOOST_CHECK(std::holds_alternative<int>(result));
	BOOST_CHECK(std::get<int>(result) == 120);
	delete funDef;
	delete functionCall;
}



BOOST_AUTO_TEST_CASE(LoadingParametersAndMapTest) {
	std::string line1 = "size: 3 x 3  obj X obj O												";
	std::string line2 = "start {																";
	std::string line3 = "		/* definiuje uklad poczatkowy planszy */						";
	std::string line4 = "			(0,0: empty), (1,0: X), (2,0: O),							";
	std::string line5 = "			(0,1: O)	, (1,1: X), (2,1: empty),						";
	std::string line6 = "			(0,2: empty), (1,2: X)										";
	std::string line7 = "}		 																";


	std::istringstream in(line1 + line2 + line3 + line4 + line5 + line6 + line7);
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));
	parser.advance();

	Interpreter interpreter;

	DefGameParameter * gameParam1 = parser.parseDefGameParameter();
	DefObject * gameParam2 = parser.parseDefObject();
	DefObject * gameParam3 = parser.parseDefObject();
	StartBlock * startBlock = parser.parseDefStart();

	exec(gameParam1, &interpreter);
	exec(gameParam2, &interpreter);
	exec(gameParam3, &interpreter);

	exec(startBlock, &interpreter);

	BOOST_CHECK(interpreter.map.getObject(0,0).value == "empty");
	BOOST_CHECK(interpreter.map.getObject(1,2).value == "X");
	BOOST_CHECK(interpreter.map.getObject(2,2).value == "empty");

	delete gameParam1;
	delete gameParam2;
	delete gameParam3;
	delete startBlock;
}


BOOST_AUTO_TEST_CASE(LoadingWholeProgramTest) {
	std::ifstream in("tictactoe.gdef.txt");
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));

	parser.advance();
	Language * lang = parser.parseLanguage();

	Interpreter interpreter(lang);

	BOOST_CHECK(interpreter.map.getObject(2, 2).value == "empty");
	BOOST_CHECK(interpreter.winner == -1);
	BOOST_CHECK(interpreter.gameFinished == false);
	BOOST_CHECK(interpreter.gameName == "tictactoe");
	BOOST_CHECK(interpreter.playersNum == 2);
	BOOST_CHECK(interpreter.functions.getFunctionDefinition("isMoveLegal") != nullptr);
	BOOST_CHECK(interpreter.functions.getFunctionDefinition("end") != nullptr);
	BOOST_CHECK(interpreter.functions.getFunctionDefinition("isWinner") != nullptr);
	BOOST_CHECK(interpreter.functions.getFunctionDefinition("isXWinner") != nullptr);
	BOOST_CHECK(interpreter.functions.getFunctionDefinition("isOWinner") != nullptr);
	BOOST_CHECK(interpreter.objs.objExists("empty") && interpreter.objs.objExists("X") && interpreter.objs.objExists("O"));

	//interpreter.run();

	delete lang;

}