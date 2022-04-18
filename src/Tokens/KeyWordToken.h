#ifndef KEYWORDTOKEN_H
#define KEYWORDTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class KeyWordToken : public Token {

public:

  enum class Type {
      KeyWordStart,
      KeyWordInt,
      KeyWordFloat,
      KeyWordBool,
      KeyWordObj,
      KeyWordTrue,
      KeyWordFalse,
      KeyWordElse,
      KeyWordIf,
      KeyWordWhile,
      KeyWordDefine,
	  KeyWordReturn
  };

  KeyWordToken(Type t);
  KeyWordToken(Type t, std::string streamName, int positionInStream);
  Type getType();
private:
   Type type;

};

#endif //KEYWORDTOKEN_H
