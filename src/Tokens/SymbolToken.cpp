#include "SymbolToken.h"

SymbolToken::SymbolToken(SymbolToken::Type t) : Token(){
  type = t;
}

SymbolToken::SymbolToken(SymbolToken::Type t, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
    type = t;
}

SymbolToken::Type SymbolToken::getType(){
  return type;
}
