#ifndef INTLITERALTOKEN_H
#define INTLITERALTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class IntLiteralToken : public Token {

public:
  IntLiteralToken(int integer);
  IntLiteralToken(int integer, std::string streamName, int positionInStream);
  IntLiteralToken(std::string integer);
  IntLiteralToken(std::string integer, std::string streamName, int positionInStream);
  int getInt();

private:
  int content;
};

#endif //INTLITERALTOKEN_H
