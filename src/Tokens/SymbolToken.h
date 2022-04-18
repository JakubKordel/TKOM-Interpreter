#ifndef SYMBOLTOKEN_H
#define SYMBOLTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class SymbolToken : public Token {

public:
  enum class Type {
    SymbolLess, // <
    SymbolGreater, // >
    SymbolLessEqual, // <=
    SymbolGreaterEqual, // >=
    SymbolEqual, // ==
    SymbolAssign, // =
    SymbolNotEqual, // !=
    SymbolNegation, // !
    SymbolAnd, // &&
    SymbolOr, // ||
    SymbolOpenRoundBracket, // (
    SymbolCloseRoundBracket, // )
    SymbolOpenCurlyBracket, // {
    SymbolCloseCurlyBracket, // }
    SymbolOpenSquereBracket, // [
    SymbolCloseSquereBracket, // ]
    SymbolSemicolon, // ;
    SymbolArrow, // ->
    SymbolDot, // .
    SymbolColon, // :
    SymbolComma, // ,
    SymbolAdd, // +
    SymbolSubstract, // -
    SymbolMultiply, // *
    SymbolDivide, // /
    SymbolX // x
  };


  SymbolToken(Type t);
  SymbolToken(Type t, std::string streamName, int positionInStream);
  Type getType();


private:
  Type type;
};

#endif //SYMBOLTOKEN_H
