#define BOOST_TEST_MODULE ScannerTests
#include <boost/test/included/unit_test.hpp>

#include <sstream>

#include <boost/test/unit_test.hpp>

#include "src/Scanner/Scanner.h"
#include "src/Tokens/Token.h"
#include "src/Tokens/tokenTypeCheck.h"

#include "src/Tokens/CommentToken.h"
#include "src/Tokens/FloatLiteralToken.h"
#include "src/Tokens/IntLiteralToken.h"
#include "src/Tokens/KeyWordToken.h"
#include "src/Tokens/SymbolToken.h"
#include "src/Tokens/WordToken.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(ScannerTests)

BOOST_AUTO_TEST_CASE(ReadingNumber) {
	std::istringstream in("123");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isIntLiteralToken(t));

	std::shared_ptr<IntLiteralToken> tc = std::dynamic_pointer_cast<IntLiteralToken>(t);

	BOOST_CHECK_EQUAL(tc->getInt(), 123);
}

BOOST_AUTO_TEST_CASE(ReadingFloat) {
	std::istringstream in("456.345");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isFloatLiteralToken(t));

	std::shared_ptr<FloatLiteralToken> tc = std::dynamic_pointer_cast<FloatLiteralToken>(t);

	BOOST_CHECK(tc->getFloat() - 456.345 < 0.01 || tc->getFloat() - 456.345 > 0.01);
}

BOOST_AUTO_TEST_CASE(ReadingComment) {
	std::istringstream in("/*comment123*comment*comment/COMMeNT*/");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isCommentToken(t));

	std::shared_ptr<CommentToken> tc = std::dynamic_pointer_cast<CommentToken>(t);

	BOOST_CHECK_EQUAL(tc->getComment(), "/*comment123*comment*comment/COMMeNT*/");
}

BOOST_AUTO_TEST_CASE(ReadingWord) {
	std::istringstream in("whilezmienna123");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isWordToken(t));

	std::shared_ptr<WordToken> tc = std::dynamic_pointer_cast<WordToken>(t);

	BOOST_CHECK_EQUAL(tc->getWord(), "whilezmienna123");
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordStart) {
	std::istringstream in("start");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordStart);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordInt) {
	std::istringstream in("int");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordInt);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordFloat) {
	std::istringstream in("float");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordFloat);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordBool) {
	std::istringstream in("bool");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordBool);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordObj) {
	std::istringstream in("obj");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordObj);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordTrue) {
	std::istringstream in("true");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordTrue);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordFalse) {
	std::istringstream in("false");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordFalse);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordElse) {
	std::istringstream in("else");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordElse);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordIf) {
	std::istringstream in("if");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordIf);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordWhile) {
	std::istringstream in("while");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordWhile);
}

BOOST_AUTO_TEST_CASE(ReadingKeyWordDefine) {
	std::istringstream in("define");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> tc = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(tc->getType() == KeyWordToken::Type::KeyWordDefine);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolLess) {
	std::istringstream in("<");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolLess);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolGreater) {
	std::istringstream in(">");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolGreater);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolLessEqual) {
	std::istringstream in("<=");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolLessEqual);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolGreaterEqual) {
	std::istringstream in(">=");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolGreaterEqual);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolEqual) {
	std::istringstream in("==");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolEqual);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolAssign) {
	std::istringstream in("=");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolAssign);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolNotEqual) {
	std::istringstream in("!=");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolNotEqual);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolNegation) {
	std::istringstream in("!");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolNegation);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolAnd) {
	std::istringstream in("&&");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolAnd);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolOr) {
	std::istringstream in("||");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolOr);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolOpenRoundBracket) {
	std::istringstream in("(");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolOpenRoundBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolCloseRoundBracket) {
	std::istringstream in(")");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolCloseRoundBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolOpenCurlyBracket) {
	std::istringstream in("{");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolOpenCurlyBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolCloseCurlyBracket) {
	std::istringstream in("}");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolCloseCurlyBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolOpenSquereBracket) {
	std::istringstream in("[");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolOpenSquereBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolCloseSquereBracket) {
	std::istringstream in("]");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolCloseSquereBracket);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolSemicolon) {
	std::istringstream in(";");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolSemicolon);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolArrow) {
	std::istringstream in("->");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolArrow);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolDot) {
	std::istringstream in(".");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolDot);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolColon) {
	std::istringstream in(":");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolColon);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolComma) {
	std::istringstream in(",");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolComma);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolAdd) {
	std::istringstream in("+");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolAdd);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolSubstract) {
	std::istringstream in("-");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolSubstract);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolMulptiply) {
	std::istringstream in("*");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolMultiply);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolDivide) {
	std::istringstream in("/");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolDivide);
}

BOOST_AUTO_TEST_CASE(ReadingSymbolX) {
	std::istringstream in("x");
	Scanner s(in);

	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> tc = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(tc->getType() == SymbolToken::Type::SymbolX);

}

BOOST_AUTO_TEST_CASE(CompoundExample) {
	std::istringstream in(" define isWinner(obj object) ");
	Scanner s(in);

	//define
	s.readNextToken();
	std::shared_ptr<Token> t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> t1 = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(t1->getType() == KeyWordToken::Type::KeyWordDefine);
	//define

	//isWinner
	s.readNextToken();
	t = s.getToken();

	BOOST_CHECK(isWordToken(t));

	std::shared_ptr<WordToken> t2 = std::dynamic_pointer_cast<WordToken>(t);

	BOOST_CHECK_EQUAL("isWinner", t2->getWord());
	//isWinner

	// (
	s.readNextToken();
	t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> t3 = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(t3->getType() == SymbolToken::Type::SymbolOpenRoundBracket);

	// (


	// obj

	s.readNextToken();
	t = s.getToken();

	BOOST_CHECK(isKeyWordToken(t));

	std::shared_ptr<KeyWordToken> t4 = std::dynamic_pointer_cast<KeyWordToken>(t);

	BOOST_CHECK(t4->getType() == KeyWordToken::Type::KeyWordObj);

	// obj

	// object
	s.readNextToken();
	t = s.getToken();

	BOOST_CHECK(isWordToken(t));

	std::shared_ptr<WordToken> t5 = std::dynamic_pointer_cast<WordToken>(t);

	BOOST_CHECK_EQUAL("object", t5->getWord());
	// object

	// )
	s.readNextToken();
	t = s.getToken();

	BOOST_CHECK(isSymbolToken(t));

	std::shared_ptr<SymbolToken> t6 = std::dynamic_pointer_cast<SymbolToken>(t);

	BOOST_CHECK(t6->getType() == SymbolToken::Type::SymbolCloseRoundBracket);
	// )
}


BOOST_AUTO_TEST_SUITE_END()
