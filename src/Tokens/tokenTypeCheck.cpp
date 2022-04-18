#include "tokenTypeCheck.h"

#include "Token.h"

bool isCommentToken(TokenVariant token){
  return std::holds_alternative<CommentToken>(token);
}

bool isFloatLiteralToken(TokenVariant token){
    return std::holds_alternative<FloatLiteralToken>(token) ;
}

bool isIntLiteralToken(TokenVariant token){
    return std::holds_alternative<IntLiteralToken>(token);
}

bool isKeyWordToken(TokenVariant token){
    return std::holds_alternative<KeyWordToken>(token);
}

bool isSymbolToken(TokenVariant token){
    return std::holds_alternative<SymbolToken>(token);
}

bool isWordToken(TokenVariant token){
    return std::holds_alternative<WordToken>(token) ;
}

bool isEmptyToken(TokenVariant token) {
	return std::holds_alternative<EmptyToken>(token);
}