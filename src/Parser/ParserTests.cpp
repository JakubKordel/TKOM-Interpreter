#define BOOST_TEST_MODULE ParserTests

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





BOOST_AUTO_TEST_CASE(TryParseWholeProgrammTest) {
	std::ifstream in("tictactoe.gdef.txt");
	auto s = std::make_unique<Scanner>(in);
	Parser parser(std::move(s));
	parser.advance();

	Language * lang = parser.parseLanguage();
	delete lang;
} 