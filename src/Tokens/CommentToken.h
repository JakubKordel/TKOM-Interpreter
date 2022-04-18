#ifndef COMMENTTOKEN_H
#define COMMENTTOKEN_H

#include <string>
#include <ostream>

#include "Token.h"

class CommentToken : public Token {

public:
  CommentToken(std::string comment);
  CommentToken(std::string comment, std::string streamName, int positionInStream);

  std::string getComment();

private:
  std::string content;
};

#endif //COMMENTTOKEN_H
