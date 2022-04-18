#include "Scanner.h"

#include <cctype>
#include <stdexcept>
#include <cwctype>



#include <iostream>

Scanner::Scanner(std::istream& in_) : in(in_), token(EmptyToken()) {
}

TokenVariant Scanner::getToken() {
	return token;
}

void Scanner::readNextToken() {
	ignoreWhiteSpaces();
	if (tryEof())
		return;
	throwOnStreamError();
	if (tryCommentToken()
		|| tryNumberToken()
		|| trySymbolToken()
		|| tryKeyWordToken()
		|| tryWordToken())
		return;
	throwUnknownToken();
}

bool Scanner::tryEof() {
	if (!in.eof())
		return false;
	token = EmptyToken();
	return true;
}

bool Scanner::tryCommentToken() {
	std::string buffer = "";
	if (!getAddCompare(buffer, '/'))
		return false;
	if (!getAddCompare(buffer, '*'))
		return false;

	bool flag = true;
	getAdd(buffer);
	while (flag) {
		while (buffer.back() != '*') {
			getAdd(buffer);
		}
		getAdd(buffer);
		if (buffer.back() == '/') {
			flag = false;
		}
	}
	token = CommentToken(buffer);
	return true;
}

bool Scanner::tryNumberToken() {
	return tryFloatLiteralToken() || tryIntLiteralToken();
}

bool Scanner::tryFloatLiteralToken() {
	std::string buffer = "";
	buffer.push_back(getNextChar());
	if (!std::isdigit(buffer.back())) {
		putBack(buffer);
		return false;
	}

	while (std::isdigit(peekNextChar())) {
		buffer.push_back(getNextChar());
	}

	if (peekNextChar() != '.') {
		putBack(buffer);
		return false;
	}

	buffer.push_back(getNextChar());

	buffer.push_back(getNextChar());
	if (!std::isdigit(buffer.back())) {
		putBack(buffer);
		return false;
	}

	while (std::isdigit(peekNextChar())) {
		buffer.push_back(getNextChar());
	}


	token = FloatLiteralToken(buffer);
	return true;

}

bool Scanner::tryIntLiteralToken() {
	std::string buffer = "";
	buffer.push_back(getNextChar());
	if (!std::isdigit(buffer.back())) {
		putBack(buffer);
		return false;
	}

	while (std::isdigit(peekNextChar())) {
		buffer.push_back(getNextChar());
	}
	token = IntLiteralToken(buffer);
	return true;
}

bool Scanner::trySymbolToken() {

	if (trySymbol("<=")) {
		token = SymbolToken(SymbolToken::Type::SymbolLessEqual);
		return true;
	}

	if (trySymbol(">=")) {
		token = SymbolToken(SymbolToken::Type::SymbolGreaterEqual);
		return true;
	}

	if (trySymbol("==")) {
		token = SymbolToken(SymbolToken::Type::SymbolEqual);
		return true;
	}

	if (trySymbol("!=")) {
		token = SymbolToken(SymbolToken::Type::SymbolNotEqual);
		return true;
	}

	if (trySymbol("&&")) {
		token = SymbolToken(SymbolToken::Type::SymbolAnd);
		return true;
	}

	if (trySymbol("||")) {
		token = SymbolToken(SymbolToken::Type::SymbolOr);
		return true;
	}

	if (trySymbol("->")) {
		token = SymbolToken(SymbolToken::Type::SymbolArrow);
		return true;
	}

	if (trySymbol("<")) {
		token = SymbolToken(SymbolToken::Type::SymbolLess);
		return true;
	}

	if (trySymbol(">")) {
		token = SymbolToken(SymbolToken::Type::SymbolGreater);
		return true;
	}

	if (trySymbol("=")) {
		token = SymbolToken(SymbolToken::Type::SymbolAssign);
		return true;
	}

	if (trySymbol("<=")) {
		token = SymbolToken(SymbolToken::Type::SymbolLessEqual);
		return true;
	}

	if (trySymbol("!")) {
		token = SymbolToken(SymbolToken::Type::SymbolNegation);
		return true;
	}

	if (trySymbol("(")) {
		token = SymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
		return true;
	}

	if (trySymbol(")")) {
		token = SymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
		return true;
	}

	if (trySymbol("{")) {
		token = SymbolToken(SymbolToken::Type::SymbolOpenCurlyBracket);
		return true;
	}

	if (trySymbol("}")) {
		token = SymbolToken(SymbolToken::Type::SymbolCloseCurlyBracket);
		return true;
	}

	if (trySymbol("[")) {
		token = SymbolToken(SymbolToken::Type::SymbolOpenSquereBracket);
		return true;
	}

	if (trySymbol("]")) {
		token = SymbolToken(SymbolToken::Type::SymbolCloseSquereBracket);
		return true;
	}

	if (trySymbol(";")) {
		token = SymbolToken(SymbolToken::Type::SymbolSemicolon);
		return true;
	}

	if (trySymbol(".")) {
		token = SymbolToken(SymbolToken::Type::SymbolDot);
		return true;
	}

	if (trySymbol(":")) {
		token = SymbolToken(SymbolToken::Type::SymbolColon);
		return true;
	}

	if (trySymbol(",")) {
		token = SymbolToken(SymbolToken::Type::SymbolComma);
		return true;
	}

	if (trySymbol("+")) {
		token = SymbolToken(SymbolToken::Type::SymbolAdd);
		return true;
	}

	if (trySymbol("-")) {
		token = SymbolToken(SymbolToken::Type::SymbolSubstract);
		return true;
	}

	if (trySymbol("*")) {
		token = SymbolToken(SymbolToken::Type::SymbolMultiply);
		return true;
	}

	if (trySymbol("/")) {
		token = SymbolToken(SymbolToken::Type::SymbolDivide);
		return true;
	}

	if (tryKeyWord("x")) {
		token = SymbolToken(SymbolToken::Type::SymbolX);
		return true;
	}

	return false;
}

bool Scanner::tryKeyWordToken() {
	if (tryKeyWord("start")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordStart);
		return true;
	}

	if (tryKeyWord("int")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordInt);
		return true;
	}

	if (tryKeyWord("float")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordFloat);
		return true;
	}

	if (tryKeyWord("bool")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordBool);
		return true;
	}

	if (tryKeyWord("obj")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordObj);
		return true;
	}

	if (tryKeyWord("true")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordTrue);
		return true;
	}

	if (tryKeyWord("false")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordFalse);
		return true;
	}

	if (tryKeyWord("else")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordElse);
		return true;
	}

	if (tryKeyWord("if")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordIf);
		return true;
	}

	if (tryKeyWord("while")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordWhile);
		return true;
	}

	if (tryKeyWord("define")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordDefine);
		return true;
	}

	if (tryKeyWord("return")) {
		token = KeyWordToken(KeyWordToken::Type::KeyWordReturn);
		return true;
	}

	return false;
}

bool Scanner::tryWordToken() {
	std::string buffer = "";
	char c = peekNextChar();
	if (!isalpha(c)) {
		return false;
	}

	while (std::iswalnum(peekNextChar()) || peekNextChar() == '_') {
		buffer.push_back(getNextChar());
	}

	token = WordToken(buffer);
	return true;
}

void Scanner::ignoreWhiteSpaces() {
	while ((streamBuf != "" || in) && std::isspace(peekNextChar()))
		getNextChar();
}

void Scanner::throwOnStreamError()
{
	if (!in)
		throw std::runtime_error("Error while reading from input");
	// TODO better error description
}

void Scanner::throwUnknownToken()
{
	const std::string msg = "Unknown token, starting with: ";
	throw std::runtime_error(msg + static_cast<char>(getNextChar()));
}

char Scanner::getNextChar() {
	if (streamBuf == "") {
		return in.get();
	}
	else {
		char r = streamBuf[0];
		streamBuf.erase(0, 1);
		return r;
	}
}

char Scanner::peekNextChar() {
	if (streamBuf == "") {
		return in.peek();
	}
	else {
		return streamBuf[0];
	}
}

void Scanner::putBack(std::string chars) {
	streamBuf = chars + streamBuf;
}

bool Scanner::tryKeyWord(std::string str) {
	std::string buffer = "";

	if (!(tryString(buffer, str))) {
		return false;
	}

	char n = peekNextChar();
	if (std::iswalnum(n)) {
		putBack(buffer);
		return false;
	}

	return true;
}

bool Scanner::trySymbol(std::string str) {
	std::string buffer = "";

	if (!(tryString(buffer, str))) {
		return false;
	}

	//eventual needs for following char

	return true;
}

bool Scanner::tryString(std::string & buffer, std::string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (!getAddCompare(buffer, str[i])) {
			return false;
		}
	}
	return true;
}

bool Scanner::getAddCompare(std::string & buf, char c) {
	buf.push_back(getNextChar());
	if (buf.back() != c) {
		putBack(buf);
		return false;
	}
	else
		return true;
}

void Scanner::getAdd(std::string & buf) {
	buf.push_back(getNextChar());
}
