
// Generated from ArcscriptLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace Arcweave {


class  ArcscriptLexer : public antlr4::Lexer {
public:
  enum {
    CODESTART = 1, PARAGRAPHSTART = 2, BLOCKQUOTESTART = 3, NORMAL_WHITESPACE = 4, 
    PARAGRAPHEND = 5, BQ_CODESTART = 6, BQ_PARAGRAPHSTART = 7, BLOCKQUOTEEND = 8, 
    BQ_WHITESPACE = 9, CODEEND = 10, MENTION_TAG_OPEN = 11, FLOAT = 12, 
    INTEGER = 13, DIGIT = 14, LPAREN = 15, RPAREN = 16, ASSIGNMUL = 17, 
    ASSIGNDIV = 18, ASSIGNADD = 19, ASSIGNSUB = 20, MUL = 21, DIV = 22, 
    ADD = 23, SUB = 24, GE = 25, GT = 26, LE = 27, LT = 28, EQ = 29, NE = 30, 
    AND = 31, OR = 32, ASSIGN = 33, NEG = 34, COMMA = 35, LBRACE = 36, RBRACE = 37, 
    BOOLEAN = 38, FNAME = 39, VFNAME = 40, VFNAMEVARS = 41, IFKEYWORD = 42, 
    ELSEKEYWORD = 43, ELSEIFKEYWORD = 44, ENDIFKEYWORD = 45, ANDKEYWORD = 46, 
    ORKEYWORD = 47, ISKEYWORD = 48, NOTKEYWORD = 49, STRING = 50, VARIABLE = 51, 
    WHITESPACE = 52, TAG_CLOSE = 53, ATTR_NAME = 54, TAG_EQUALS = 55, MENTION_TAG_CLOSE = 56, 
    TAG_WHITESPACE = 57, TAG_OPEN = 58, MENTION_LABEL = 59, ATTR_VALUE = 60, 
    ATTRIBUTE = 61
  };

  enum {
    PARAGRAPH = 1, BLOCKQUOTE = 2, CODESEGMENT = 3, MENTIONSEGMENT = 4, 
    MENTIONLABELSEGMENT = 5, MENTION_ATTR_SEGMENT = 6
  };

  explicit ArcscriptLexer(antlr4::CharStream *input);

  ~ArcscriptLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace Arcweave
