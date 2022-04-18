#pragma once

#include "../Scanner/Scanner.h"
#include "../ast/AstNode.h"

#include "../Tokens/Token.h"

#include <vector>
#include <utility>
#include <string>

//#include "../VariantsDefinitions/variantsDefinitons.h"
typedef std::variant<WhileLoop*, IfStatement*, Block*, StartBlock*, Language*, ReturnStatement*, FunctionCall*, ValueAssignment*, DefObject*, DefFunction*, DefGameParameter*, LocalVariableDeclaration*> Executable;
typedef std::variant<ExpressionNode*, BracketsName*, FloatLiteral*, IntLiteral*, VariableName*, FunctionCall*, TrueFalseLiteral*> Evaluable;
typedef std::variant<CommentToken, FloatLiteralToken, IntLiteralToken, KeyWordToken, SymbolToken, WordToken, EmptyToken> TokenVariant;

class Parser {
public:

	enum class TokenType {
		Comment,
		FloatLiteral,
		IntLiteral,
		Symbol,
		KeyWord,
		Word,
		EndOfFile
	};


	Parser(std::unique_ptr<Scanner> s);

	Language * parseLanguage();
	Executable parseDefinition();
	DefGameParameter * parseDefGameParameter();
	void parseParameterValue(DefGameParameter * parameter);
	StartBlock * parseDefStart();
	StartBlock * parseStartBlock();
	std::vector<SquereDeclaration> parseStartBlockContent();
	std::vector<SquereDeclaration> parseSqueresDefinition();
	SquereDeclaration parseSquereDefinition();
	DefObject * parseDefObject();
	DefFunction * parseDefFunction();
	VariableType parseReturnTypeDefinition(DefFunction * function);
	std::vector<std::pair<VariableType, std::string>> parseParametersList();
	std::pair<VariableType, std::string> parseFunctionArgumentDeclaration();
	Block * parseBlock();
	void parseBlockContent(Block * block);
	Executable parseStatement();
	ReturnStatement * parseReturnStatement();
	Executable parseValueAssignmentOrFunctionCall();
	LocalVariableDeclaration * parseLocalVariableDeclaration();
	WhileLoop * parseWhileLoop();
	IfStatement * parseIfStatement();
	Block * parseElseClause();
	Evaluable parseIfHeader();
	void parseArgumentsClause(FunctionCall * functionCall);
	void parseArgumentsList(FunctionCall * functionCall);
	Evaluable parseExpression();
	Evaluable parseAndExpression();
	Evaluable parseEqualityExpression();
	Evaluable parseRelationalExpression();
	Evaluable parseAddSubstractExpression();
	Evaluable parseTerm();
	Evaluable parsePrimary();
	Evaluable parseParenthExpression();
	Evaluable parseIdentificator();
	Evaluable parseSquereBracket();
	void parseSquereBrackets(BracketsName * bracketsName);
	VariableType parseTypeName();

	std::unique_ptr<SymbolToken> requireSymbolToken(const SymbolToken::Type type);
	std::unique_ptr < KeyWordToken > requireKeyWordToken(const KeyWordToken::Type type);
	std::unique_ptr < FloatLiteralToken > requireFloatLiteralToken();
	std::unique_ptr < IntLiteralToken > requireIntLiteralToken();
	std::unique_ptr < WordToken > requireWordToken();

	bool checkTokenType(TokenType tokenType) const;

	void advance();

	bool checkSymbolToken(const SymbolToken::Type type) const;
	bool checkKeyWordToken(const KeyWordToken::Type type) const;

	bool isRelationalSymbolToken();

	void throwUnexpectedTokenError();


private:
	int tokensCounter = 0;
		std::unique_ptr<Scanner> scanner;

	
};

