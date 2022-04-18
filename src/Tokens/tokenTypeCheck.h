#ifndef TOKENTYPECHECK_H
#define TOKENTYPECHECK_H

#include "Token.h"
#include <memory>


typedef std::variant<CommentToken, FloatLiteralToken, IntLiteralToken, KeyWordToken, SymbolToken, WordToken, EmptyToken> TokenVariant;

bool isCommentToken(TokenVariant token);

bool isFloatLiteralToken(TokenVariant token);

bool isIntLiteralToken(TokenVariant token);

bool isKeyWordToken(TokenVariant token);

bool isSymbolToken(TokenVariant token);

bool isWordToken(TokenVariant token);

bool isEmptyToken(TokenVariant token);

#endif //TOKENTYPECHECK_H
