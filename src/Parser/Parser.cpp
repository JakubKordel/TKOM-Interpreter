#include "Parser.h"
#include "../Tokens/tokenTypeCheck.h"
#include "../EnumClasses/OperatorType.h"

#include <variant>

Parser::Parser(std::unique_ptr<Scanner> s) : scanner(std::move(s)){

}

Language * Parser::parseLanguage() {
	Language * root = new Language();
	while (!checkTokenType(TokenType::EndOfFile)) {
		root->addDefinition(parseDefinition());
	}
	return root;
}


Executable Parser::parseDefinition() {
	if (checkKeyWordToken(KeyWordToken::Type::KeyWordStart)) {
		return parseDefStart();
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordObj)) {
		return parseDefObject();
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordDefine)) {
		return parseDefFunction();
	}
	else if (checkTokenType(TokenType::Word)) {
		return parseDefGameParameter();
	}
	else {
		throwUnexpectedTokenError();
	}
}

DefGameParameter * Parser::parseDefGameParameter() {
	DefGameParameter * parameter = new DefGameParameter();
	parameter->setParameterName(requireWordToken()->getWord());
	requireSymbolToken(SymbolToken::Type::SymbolColon);
	parseParameterValue(parameter);
	return parameter;
}

void Parser::parseParameterValue(DefGameParameter * parameter) {
	if (checkTokenType(TokenType::Word)) {
		parameter->setValueType(DefGameParameter::ValueType::Word);
		parameter->setWordValue(requireWordToken()->getWord());
	}
	else if (checkTokenType(TokenType::IntLiteral)) {
		int x = requireIntLiteralToken()->getInt();
		if (checkSymbolToken(SymbolToken::Type::SymbolX)) {
			advance();
			int y = requireIntLiteralToken()->getInt();
			parameter->setValueType(DefGameParameter::ValueType::Pair);
			parameter->setPairValue(std::pair<int, int>(x, y));
		}
		else {
			parameter->setValueType(DefGameParameter::ValueType::Integer);
			parameter->setIntValue(x);
		}
	}
	else {
		throwUnexpectedTokenError();
	}
}

StartBlock * Parser::parseDefStart() {
	requireKeyWordToken(KeyWordToken::Type::KeyWordStart);
	return parseStartBlock();
}

StartBlock * Parser::parseStartBlock() {
	requireSymbolToken(SymbolToken::Type::SymbolOpenCurlyBracket);
	std::vector<SquereDeclaration> squeresDeclaration = parseStartBlockContent();
	requireSymbolToken(SymbolToken::Type::SymbolCloseCurlyBracket);
	StartBlock * startBlock = new StartBlock();
	for (auto it = squeresDeclaration.begin(); it != squeresDeclaration.end(); ++it) {
		startBlock->addDeclaredSquere(*it);
	}
	return startBlock;
}

std::vector<SquereDeclaration> Parser::parseStartBlockContent() {
	if (checkSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket)) {
		return parseSqueresDefinition();
	}
	else {
		std::vector<SquereDeclaration> emptyVector;
		return emptyVector;
	}
}

std::vector<SquereDeclaration> Parser::parseSqueresDefinition() {
	std::vector<SquereDeclaration> squeres;
	squeres.push_back(parseSquereDefinition());
	while (checkSymbolToken(SymbolToken::Type::SymbolComma)) {
		advance();
		squeres.push_back(parseSquereDefinition());
	}
	return squeres;
}

SquereDeclaration Parser::parseSquereDefinition() {
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	auto xToken = requireIntLiteralToken();
	requireSymbolToken(SymbolToken::Type::SymbolComma);
	auto yToken = requireIntLiteralToken();
	requireSymbolToken(SymbolToken::Type::SymbolColon);
	auto nameToken = requireWordToken();
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
	return SquereDeclaration(xToken->getInt(), yToken->getInt(), nameToken->getWord());
}

DefObject * Parser::parseDefObject() {
	requireKeyWordToken(KeyWordToken::Type::KeyWordObj);
	auto objName = requireWordToken();
	return new DefObject(objName->getWord());
}

DefFunction * Parser::parseDefFunction() {
	DefFunction * functionDefinition = new DefFunction();

	requireKeyWordToken(KeyWordToken::Type::KeyWordDefine);
	std::unique_ptr<WordToken> funName = requireWordToken();
	functionDefinition->setFunctionName(funName->getWord());
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	if (!checkSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket)) {
		functionDefinition->setParameters(parseParametersList());
	}
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
	if (!checkSymbolToken(SymbolToken::Type::SymbolOpenCurlyBracket)) {
		functionDefinition->setReturnType(parseReturnTypeDefinition(functionDefinition));
	}
	else {
		functionDefinition->setReturnType(VariableType::Void);
	}
	functionDefinition->setBlock(parseBlock());
	return functionDefinition;
}

VariableType Parser::parseReturnTypeDefinition(DefFunction * function) {
	requireSymbolToken(SymbolToken::Type::SymbolArrow);
	return parseTypeName();
}

std::vector<std::pair<VariableType, std::string>> Parser::parseParametersList() {
	std::vector<std::pair<VariableType, std::string>> arguments;
	arguments.push_back(parseFunctionArgumentDeclaration());
	while (checkSymbolToken(SymbolToken::Type::SymbolComma)) {
		advance();
		arguments.push_back(parseFunctionArgumentDeclaration());
	}
	return arguments;
}

std::pair<VariableType, std::string> Parser::parseFunctionArgumentDeclaration() {
	std::pair<VariableType, std::string> argument;
	argument.first = parseTypeName();
	argument.second = requireWordToken()->getWord();
	return argument;
}

Block * Parser::parseBlock() {
	auto block = new Block();
	requireSymbolToken(SymbolToken::Type::SymbolOpenCurlyBracket);
	parseBlockContent(block);
	requireSymbolToken(SymbolToken::Type::SymbolCloseCurlyBracket);
	return block;
}

void Parser::parseBlockContent(Block * block) {
	while (!checkSymbolToken(SymbolToken::Type::SymbolCloseCurlyBracket)) {
		block->addInstruction(parseStatement());
	}
}

Executable Parser::parseStatement() {
	if (checkKeyWordToken(KeyWordToken::Type::KeyWordWhile)) {
		return parseWhileLoop();
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordIf)) {
		return parseIfStatement();
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordReturn)) {
		return parseReturnStatement();
	}
	else  if (checkKeyWordToken(KeyWordToken::Type::KeyWordObj) || checkKeyWordToken(KeyWordToken::Type::KeyWordInt) ||
		checkKeyWordToken(KeyWordToken::Type::KeyWordFloat) || checkKeyWordToken(KeyWordToken::Type::KeyWordBool)) {
		return parseLocalVariableDeclaration();
	}
	else if (checkTokenType(TokenType::Word)) {
		return parseValueAssignmentOrFunctionCall();
	}
	else {
		throwUnexpectedTokenError();
	}

}

ReturnStatement * Parser::parseReturnStatement() {
	auto returnStatement = new ReturnStatement();
	requireKeyWordToken(KeyWordToken::Type::KeyWordReturn);
	returnStatement->setValue(parseExpression());
	requireSymbolToken(SymbolToken::Type::SymbolSemicolon);
	return returnStatement;
}

Executable Parser::parseValueAssignmentOrFunctionCall() {
	std::string word = requireWordToken()->getWord();
	if (checkSymbolToken(SymbolToken::Type::SymbolAssign)) {
		advance();
		auto valueAssignment = new ValueAssignment();
		valueAssignment->setVariableName(word);
		valueAssignment->setValue(parseExpression());
		requireSymbolToken(SymbolToken::Type::SymbolSemicolon);
		return valueAssignment;
	}
	else if (checkSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket)) {
		auto functionCall = new FunctionCall();
		functionCall->setName(word);
		parseArgumentsClause(functionCall);
		requireSymbolToken(SymbolToken::Type::SymbolSemicolon);
		return functionCall;
	}
	else {
		throwUnexpectedTokenError();
	}
}

LocalVariableDeclaration * Parser::parseLocalVariableDeclaration() {
	auto variableDeclaration = new LocalVariableDeclaration();
	variableDeclaration->setType(parseTypeName());
	variableDeclaration->setName(requireWordToken()->getWord());
	requireSymbolToken(SymbolToken::Type::SymbolAssign);
	variableDeclaration->setValue(parseExpression());
	requireSymbolToken(SymbolToken::Type::SymbolSemicolon);
	return variableDeclaration;
}

WhileLoop * Parser::parseWhileLoop() {
	auto whileLoop = new WhileLoop();
	requireKeyWordToken(KeyWordToken::Type::KeyWordWhile);
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	whileLoop->setCondition(parseExpression());
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
	whileLoop->setBlock(parseBlock());
	return whileLoop;
}

IfStatement * Parser::parseIfStatement() {
	auto ifStatement = new IfStatement();
	ifStatement->setCondition(parseIfHeader());
	ifStatement->setTrueBlock(parseBlock());
	if (checkKeyWordToken(KeyWordToken::Type::KeyWordElse)) {
		ifStatement->setFalseBlock(parseElseClause());
	}
	else {
		ifStatement->setFalseBlock(nullptr);
	}
	return ifStatement;
}

Block * Parser::parseElseClause() {
	requireKeyWordToken(KeyWordToken::Type::KeyWordElse);
	if (checkKeyWordToken(KeyWordToken::Type::KeyWordIf)) {
		auto elseIfBlock = new Block();
		elseIfBlock->addInstruction(parseIfStatement());
		return elseIfBlock;
	}
	else if (checkSymbolToken(SymbolToken::Type::SymbolOpenCurlyBracket)) {
		return parseBlock();
	}
	else {
		throwUnexpectedTokenError();
		return nullptr;
	}
}

Evaluable Parser::parseIfHeader() {
	requireKeyWordToken(KeyWordToken::Type::KeyWordIf);
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	auto expr = parseExpression();
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
	return expr;
}

void Parser::parseArgumentsClause(FunctionCall * functionCall) {
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	if (!checkSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket)) {
		parseArgumentsList(functionCall);
	}
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
}


void Parser::parseArgumentsList(FunctionCall * functionCall) {
	functionCall->addArgument(parseExpression());
	while (checkSymbolToken(SymbolToken::Type::SymbolComma)) {
		advance();
		functionCall->addArgument(parseExpression());
	}
}

Evaluable Parser::parseExpression() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();

	auto firstOperand = parseAndExpression();
	expressionNode->addOperand(firstOperand);
	while (checkSymbolToken(SymbolToken::Type::SymbolOr)) {
		flag = true;
		advance();
		expressionNode->addOperator(OperatorType::Or);
		expressionNode->addOperand(parseAndExpression());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parseAndExpression() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();
	auto firstOperand = parseEqualityExpression();
	expressionNode->addOperand(firstOperand);

	while (checkSymbolToken(SymbolToken::Type::SymbolAnd)) {
		flag = true;
		advance();
		expressionNode->addOperator(OperatorType::And);
		expressionNode->addOperand(parseEqualityExpression());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parseEqualityExpression() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();
	auto firstOperand = parseRelationalExpression();
	expressionNode->addOperand(firstOperand);
	if (checkSymbolToken(SymbolToken::Type::SymbolEqual) || checkSymbolToken(SymbolToken::Type::SymbolNotEqual)) {
		flag = true;
		if (checkSymbolToken(SymbolToken::Type::SymbolEqual)) {
			expressionNode->addOperator(OperatorType::Equal);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolNotEqual)) {
			expressionNode->addOperator(OperatorType::NotEqual);
		}
		advance();
		expressionNode->addOperand(parseRelationalExpression());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parseRelationalExpression() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();
	auto firstOperand = parseAddSubstractExpression();
	expressionNode->addOperand(firstOperand);
	if (isRelationalSymbolToken()) {
		flag = true;
		if (checkSymbolToken(SymbolToken::Type::SymbolGreater)) {
			expressionNode->addOperator(OperatorType::Greater);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolLess)) {
			expressionNode->addOperator(OperatorType::Less);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolGreaterEqual)) {
			expressionNode->addOperator(OperatorType::GreaterEqual);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolLessEqual)) {
			expressionNode->addOperator(OperatorType::LessEqual);
		}
		advance();
		expressionNode->addOperand(parseAddSubstractExpression());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parseAddSubstractExpression() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();
	auto firstOperand = parseTerm();
	expressionNode->addOperand(firstOperand);
	while (checkSymbolToken(SymbolToken::Type::SymbolAdd) || checkSymbolToken(SymbolToken::Type::SymbolSubstract)) {
		flag = true;
		if (checkSymbolToken(SymbolToken::Type::SymbolAdd)) {
			expressionNode->addOperator(OperatorType::Add);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolSubstract)) {
			expressionNode->addOperator(OperatorType::Substract);
		}
		advance();
		expressionNode->addOperand(parseTerm());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parseTerm() {
	bool flag = false;
	auto expressionNode = new ExpressionNode();
	Evaluable firstOperand = parsePrimary();
	expressionNode->addOperand(firstOperand);
	while (checkSymbolToken(SymbolToken::Type::SymbolMultiply) || checkSymbolToken(SymbolToken::Type::SymbolDivide)) {
		flag = true;
		if (checkSymbolToken(SymbolToken::Type::SymbolMultiply)) {
			expressionNode->addOperator(OperatorType::Multiply);
		}
		else if (checkSymbolToken(SymbolToken::Type::SymbolDivide)) {
			expressionNode->addOperator(OperatorType::Divide);
		}
		advance();
		expressionNode->addOperand(parsePrimary());
	}
	if (flag) {
		return expressionNode;
	}
	else {
		expressionNode->operands.clear();
		delete expressionNode;
		return firstOperand;
	}
}

Evaluable Parser::parsePrimary() {
	bool flag = false;
	auto unaryExpression = new ExpressionNode();
	if (checkSymbolToken(SymbolToken::Type::SymbolSubstract)) {
		advance();
		flag = true;
		unaryExpression->addOperator(OperatorType::Substract);
	}
	else if (checkSymbolToken(SymbolToken::Type::SymbolNegation)) {
		advance();
		flag = true;
		unaryExpression->addOperator(OperatorType::Negation);
	}

	if (checkTokenType(TokenType::IntLiteral)) {
		IntLiteral * literal = new IntLiteral();
		literal->setValue(requireIntLiteralToken()->getInt());
		if (flag) {
			unaryExpression->addOperand(literal);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return literal;
		}
	}
	else if (checkTokenType(TokenType::FloatLiteral)) {
		auto literal = new FloatLiteral();
		literal->setValue(requireFloatLiteralToken()->getFloat());
		if (flag) {
			unaryExpression->addOperand(literal);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return literal;
		}
	}
	else if (checkSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket)) {
		auto expr = parseParenthExpression();
		if (flag) {
			unaryExpression->addOperand(expr);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return expr;
		}
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordTrue)) {
		advance();
		auto trueValue = new TrueFalseLiteral();
		trueValue->setValue(true);
		if (flag) {
			unaryExpression->addOperand(trueValue);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return trueValue;
		}
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordFalse)) {
		advance();
		auto falseValue = new TrueFalseLiteral();
		falseValue->setValue(false);
		if (flag) {
			unaryExpression->addOperand(falseValue);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return falseValue;
		}
	}
	else if (checkTokenType(TokenType::Word)) {
		auto id = parseIdentificator();
		if (flag) {
			unaryExpression->addOperand(id);
			return unaryExpression;
		}
		else {
			delete unaryExpression;
			return id;
		}

	}
	else {
		throwUnexpectedTokenError();
	}
}


Evaluable Parser::parseParenthExpression() {
	requireSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket);
	auto expr = parseExpression();
	requireSymbolToken(SymbolToken::Type::SymbolCloseRoundBracket);
	return expr;
}

Evaluable Parser::parseIdentificator() {
	auto word = requireWordToken();
	if (checkSymbolToken(SymbolToken::Type::SymbolOpenRoundBracket)) {
		FunctionCall * functionCall = new FunctionCall();
		functionCall->setName(word->getWord());
		parseArgumentsClause(functionCall);
		return functionCall;
	}
	else if (checkSymbolToken(SymbolToken::Type::SymbolOpenSquereBracket)) {
		auto bracketsName = new BracketsName();
		bracketsName->setName(word->getWord());
		parseSquereBrackets(bracketsName);
		return bracketsName;
	}
	else {
		VariableName * variableName = new VariableName();
		variableName->setName(word->getWord());
		return variableName;
	}
}

Evaluable Parser::parseSquereBracket() {
	requireSymbolToken(SymbolToken::Type::SymbolOpenSquereBracket);
	auto expr = parseExpression();
	requireSymbolToken(SymbolToken::Type::SymbolCloseSquereBracket);
	return expr;
}

void Parser::parseSquereBrackets(BracketsName * bracketsName) {
	bracketsName->addValue(parseSquereBracket());
	while (checkSymbolToken(SymbolToken::Type::SymbolOpenSquereBracket)) {
		bracketsName->addValue(parseSquereBracket());
	}
}

VariableType Parser::parseTypeName() {
	if (checkKeyWordToken(KeyWordToken::Type::KeyWordInt)) {
		advance();
		return VariableType::Int;
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordFloat)) {
		advance();
		return VariableType::Float;
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordBool)) {
		advance();
		return VariableType::Bool;
	}
	else if (checkKeyWordToken(KeyWordToken::Type::KeyWordObj)) {
		advance();
		return VariableType::Obj;
	}
	else {
		throwUnexpectedTokenError();
		return VariableType();
	}
}

std::unique_ptr<SymbolToken> Parser::requireSymbolToken(const SymbolToken::Type type) {
	if (!checkSymbolToken(type)) {
		throwUnexpectedTokenError();
		return nullptr;
	}
	else {
		TokenVariant token = scanner->getToken();
		advance();
		return std::make_unique<SymbolToken>(std::get<SymbolToken>(token));
	}
}

std::unique_ptr<KeyWordToken> Parser::requireKeyWordToken(const KeyWordToken::Type type) {
	if (!checkKeyWordToken(type)) {
		throwUnexpectedTokenError();
		return nullptr;
	}
	else {
		TokenVariant token = scanner->getToken();
		advance();
		return std::make_unique<KeyWordToken>(std::get<KeyWordToken>(token));
	}
}

std::unique_ptr<FloatLiteralToken> Parser::requireFloatLiteralToken() {
	if (!checkTokenType(TokenType::FloatLiteral)) {
		throwUnexpectedTokenError();
		return nullptr;
	}
	else {
		TokenVariant token = scanner->getToken();
		advance();
		return std::make_unique<FloatLiteralToken>(std::get<FloatLiteralToken>(token));
	}
}

std::unique_ptr<IntLiteralToken> Parser::requireIntLiteralToken() {
	if (!checkTokenType(TokenType::IntLiteral)) {
		throwUnexpectedTokenError();
		return nullptr;
	}
	else {
		TokenVariant token = scanner->getToken();
		advance();
		return std::make_unique<IntLiteralToken>(std::get<IntLiteralToken>(token));
	}
}

std::unique_ptr<WordToken> Parser::requireWordToken() {
	if (!checkTokenType(TokenType::Word)) {
		throwUnexpectedTokenError();
		return nullptr;
	}
	else {
		TokenVariant token = scanner->getToken();
		advance();
		return std::make_unique<WordToken>(std::get<WordToken>(token));
	}
}

bool Parser::checkTokenType(TokenType tokenType) const {
	switch (tokenType) {
	case TokenType::Comment:
		return isCommentToken(scanner->getToken());
		break;
	case TokenType::FloatLiteral:
		return isFloatLiteralToken(scanner->getToken());
		break;
	case TokenType::IntLiteral:
		return isIntLiteralToken(scanner->getToken());
		break;
	case TokenType::Symbol:
		return isSymbolToken(scanner->getToken());
		break;
	case TokenType::KeyWord:
		return isKeyWordToken(scanner->getToken());
		break;
	case TokenType::Word:
		return isWordToken(scanner->getToken());
		break;
	case TokenType::EndOfFile:
		return isEmptyToken(scanner->getToken());
		break;
	}
	return false;
}

void Parser::advance() {
	do {
		scanner->readNextToken();
		++tokensCounter;
	} while (checkTokenType(TokenType::Comment));
}

bool Parser::checkSymbolToken(const SymbolToken::Type type) const {
	if (!checkTokenType(TokenType::Symbol)) {
		return false;
	}
	else {
		std::unique_ptr<SymbolToken> p = std::make_unique<SymbolToken>(std::get<SymbolToken>(scanner->getToken()));
		return p->getType() == type;
	}
}

bool Parser::checkKeyWordToken(const KeyWordToken::Type type) const {
	if (!checkTokenType(TokenType::KeyWord)) {
		return false;
	}
	else {
		std::unique_ptr<KeyWordToken> p = std::make_unique<KeyWordToken>(std::get<KeyWordToken>(scanner->getToken()));
		return p->getType() == type;
	}
}

bool Parser::isRelationalSymbolToken() {
	return checkSymbolToken(SymbolToken::Type::SymbolGreater)
		|| checkSymbolToken(SymbolToken::Type::SymbolLess)
		|| checkSymbolToken(SymbolToken::Type::SymbolLessEqual)
		|| checkSymbolToken(SymbolToken::Type::SymbolGreaterEqual)
		;
}

void Parser::throwUnexpectedTokenError() {
	throw std::runtime_error("Unexpected token at " + std::to_string(tokensCounter) + " token");
}
