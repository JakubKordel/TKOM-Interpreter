#include "WordToken.h"

WordToken::WordToken(std::string w) : Token(){
  word = w;
}

WordToken::WordToken(std::string w, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  word = w;
}


std::string WordToken::getWord(){
  return word;
}
