cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project("GameDefLanguage")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SCANNER_DIR src/Scanner)
set(PARSER_DIR src/Parser)
set(INTERPRETER_DIR src/Interpreter)
set(TOKENS_DIR src/Tokens)
set(VARIANTS_DIR src/VariantsDefinitions)
set(AST_DIR src/ast)

set(SOURCES

    ${SCANNER_DIR}/Scanner.cpp

    ${PARSER_DIR}/Parser.cpp

    ${INTERPRETER_DIR}/Interpreter.cpp
    ${INTERPRETER_DIR}/InterpreterStructures/Evaluation.cpp
    ${INTERPRETER_DIR}/InterpreterStructures/Execution.cpp
    ${INTERPRETER_DIR}/InterpreterStructures/ObjValue.cpp
    ${INTERPRETER_DIR}/InterpreterStructures/VoidValue.cpp

    ${TOKENS_DIR}/CommentToken.cpp
    ${TOKENS_DIR}/EmptyToken.cpp
    ${TOKENS_DIR}/FloatLiteralToken.cpp
    ${TOKENS_DIR}/IntLiteralToken.cpp
    ${TOKENS_DIR}/KeyWordToken.cpp
    ${TOKENS_DIR}/SymbolToken.cpp
    ${TOKENS_DIR}/Token.cpp
    ${TOKENS_DIR}/tokenTypeCheck.cpp
    ${TOKENS_DIR}/WordToken.cpp

    ${AST_DIR}/nodes/Block.cpp
    ${AST_DIR}/nodes/BracketsName.cpp
    ${AST_DIR}/nodes/DefFunction.cpp
    ${AST_DIR}/nodes/DefGameParameter.cpp
    ${AST_DIR}/nodes/DefObject.cpp
    ${AST_DIR}/nodes/ExpressionNode.cpp
    ${AST_DIR}/nodes/FloatLiteral.cpp
    ${AST_DIR}/nodes/FunctionCall.cpp
    ${AST_DIR}/nodes/IfStatement.cpp
    ${AST_DIR}/nodes/IntLiteral.cpp
    ${AST_DIR}/nodes/Language.cpp
    ${AST_DIR}/nodes/LocalVariableDeclaration.cpp
    ${AST_DIR}/nodes/ReturnStatement.cpp
    ${AST_DIR}/nodes/StartBlock.cpp
    ${AST_DIR}/nodes/TrueFalseLiteral.cpp
    ${AST_DIR}/nodes/ValueAssignment.cpp
    ${AST_DIR}/nodes/VariableName.cpp
    ${AST_DIR}/nodes/WhileLoop.cpp
    main.cpp
)

add_executable(rungame ${SOURCES})

target_include_directories(rungame PUBLIC src)
