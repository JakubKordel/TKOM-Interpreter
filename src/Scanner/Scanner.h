#ifndef SCANNER_H
#define SCANNER_H

#include <istream>

#include "../Tokens/Token.h"

#include <memory>
#include <variant>

typedef std::variant<CommentToken, FloatLiteralToken, IntLiteralToken, KeyWordToken, SymbolToken, WordToken, EmptyToken> TokenVariant;

class Scanner{
public:
  Scanner(std::istream& in);

  Scanner(const Scanner&) = delete;
  const Scanner& operator=(const Scanner&) = delete;

  void readNextToken();
  TokenVariant getToken();

private:
  bool tryEof();
  bool tryCommentToken();
  bool tryNumberToken();
  bool trySymbolToken();
  bool tryKeyWordToken();
  bool tryWordToken();

  char getNextChar(); //gets next char either from stream or from streamBuf (if chars were already taken from stream )
  char peekNextChar();
  void putBack(std::string chars); //returns chars to streamBuf


  void getAdd(std::string & buf);

  bool getAddCompare(std::string & buf, char c);

  bool tryFloatLiteralToken();

  bool tryIntLiteralToken();

  bool tryKeyWord(std::string str);

  bool trySymbol(std::string str);

  bool tryString(std::string & buffer, std::string str);



  void ignoreWhiteSpaces();
  void throwUnknownToken();
  void throwOnStreamError();

  std::istream& in;
  std::string streamBuf = "";
  TokenVariant token;
};


#endif // SCANNER_H
