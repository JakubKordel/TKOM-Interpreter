#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

class Token {

public:


  Token(std::string streamName = "", int position = -1);

  int getStartingPositionInStream();
  std::string getStreamName();

  virtual ~Token() = default;

private:
  int positionInStream;
  std::string stream;
};


#include "CommentToken.h"
#include "FloatLiteralToken.h"
#include "IntLiteralToken.h"
#include "KeyWordToken.h"
#include "SymbolToken.h"
#include "WordToken.h"
#include "EmptyToken.h"




#endif //TOKEN_H
