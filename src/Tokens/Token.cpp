#include "Token.h"

Token::Token(std::string streamName, int startingPosition){
  stream = streamName;
  positionInStream = startingPosition;
}

int Token::getStartingPositionInStream(){
  return positionInStream;
}

std::string Token::getStreamName(){
  return stream;
}
