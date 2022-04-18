#ifndef FLOATLITERALTOKEN_H
#define FLOATLITERALTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class FloatLiteralToken : public Token {

public:
  FloatLiteralToken(float floatNumber);
  FloatLiteralToken(float floatNumber, std::string streamName, int positionInStream);
  FloatLiteralToken(std::string floatNumber);
  FloatLiteralToken(std::string floatNumber, std::string streamName, int positionInStream);
  float getFloat();

private:
  float content;
};

#endif //FLOATLITERALTOKEN_H
