#ifndef WORDTOKEN_H
#define WORDTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class WordToken : public Token {

public:

  WordToken(std::string w);
  WordToken(std::string w, std::string streamName, int positionInStream);
  std::string getWord();
  
private:
  std::string word;
};

#endif //WORDTOKEN_H
