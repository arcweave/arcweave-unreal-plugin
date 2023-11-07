
// Generated from ArcscriptLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"


namespace Arcweave {


class  ArcscriptLexer : public antlr4::Lexer {
public:
  enum {
    CODESTART = 1, NORMALTEXT = 2, CODEEND = 3, MENTION_TAG_OPEN = 4, FLOAT = 5, 
    INTEGER = 6, DIGIT = 7, LPAREN = 8, RPAREN = 9, ASSIGNMUL = 10, ASSIGNDIV = 11, 
    ASSIGNADD = 12, ASSIGNSUB = 13, MUL = 14, DIV = 15, ADD = 16, SUB = 17, 
    GE = 18, GT = 19, LE = 20, LT = 21, EQ = 22, NE = 23, AND = 24, OR = 25, 
    ASSIGN = 26, NEG = 27, COMMA = 28, LBRACE = 29, RBRACE = 30, BOOLEAN = 31, 
    FNAME = 32, VFNAME = 33, VFNAMEVARS = 34, IFKEYWORD = 35, ELSEKEYWORD = 36, 
    ELSEIFKEYWORD = 37, ENDIFKEYWORD = 38, ANDKEYWORD = 39, ORKEYWORD = 40, 
    ISKEYWORD = 41, NOTKEYWORD = 42, STRING = 43, VARIABLE = 44, WHITESPACE = 45, 
    TAG_CLOSE = 46, ATTR_NAME = 47, TAG_EQUALS = 48, MENTION_TAG_CLOSE = 49, 
    TAG_WHITESPACE = 50, TAG_OPEN = 51, MENTION_LABEL = 52, ATTR_VALUE = 53, 
    ATTRIBUTE = 54
  };

  enum {
    CODESEGMENT = 1, MENTIONSEGMENT = 2, MENTIONLABELSEGMENT = 3, MENTION_ATTR_SEGMENT = 4
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
