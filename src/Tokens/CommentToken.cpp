#include "CommentToken.h"

CommentToken::CommentToken(std::string comment) : Token() {
  content = comment;
}

CommentToken::CommentToken(std::string comment, std::string streamName, int positionInStream) : Token(streamName, positionInStream){
  content = comment;

}

std::string CommentToken::getComment() {
  return content;
}
