#include "IntLiteralToken.h"

IntLiteralToken::IntLiteralToken(int integer) : Token(){
  content = integer;
}

IntLiteralToken::IntLiteralToken(int integer, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  content = integer;
}

IntLiteralToken::IntLiteralToken(std::string integer) : Token(){
  content = std::stoi( integer );
}

IntLiteralToken::IntLiteralToken(std::string integer, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  content = std::stoi( integer );
}

int IntLiteralToken::getInt(){
  return content;
}
