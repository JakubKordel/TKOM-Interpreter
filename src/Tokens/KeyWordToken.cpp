#include "KeyWordToken.h"

KeyWordToken::KeyWordToken(KeyWordToken::Type t) : Token(){
  type = t;
}

KeyWordToken::KeyWordToken(KeyWordToken::Type t, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  type = t;
}

KeyWordToken::Type KeyWordToken::getType(){
  return type;
}
