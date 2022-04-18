#include "FloatLiteralToken.h"

FloatLiteralToken::FloatLiteralToken(float floatNumber) : Token(){
  content = floatNumber;
}

FloatLiteralToken::FloatLiteralToken(float floatNumber, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  content = floatNumber;
}

FloatLiteralToken::FloatLiteralToken(std::string floatNumber) : Token(){
  content = std::stof( floatNumber );
}

FloatLiteralToken::FloatLiteralToken(std::string floatNumber, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  content = std::stof( floatNumber );
}

float FloatLiteralToken::getFloat(){
  return content;
}
