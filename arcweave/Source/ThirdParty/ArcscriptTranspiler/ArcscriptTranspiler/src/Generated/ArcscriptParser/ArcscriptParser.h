
// Generated from ArcscriptParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"

#include "ArcscriptParserBase.h"

namespace Arcweave {


class  ArcscriptParser : public ArcscriptParserBase {
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
    RuleInput = 0, RuleScript = 1, RuleScript_section = 2, RuleBlockquote = 3, 
    RuleParagraph = 4, RuleParagraph_start = 5, RuleCodestart = 6, RuleCodeend = 7, 
    RuleAssignment_segment = 8, RuleFunction_call_segment = 9, RuleConditional_section = 10, 
    RuleIf_section = 11, RuleElse_if_section = 12, RuleElse_section = 13, 
    RuleIf_clause = 14, RuleElse_if_clause = 15, RuleEndif_segment = 16, 
    RuleStatement_assignment = 17, RuleStatement_function_call = 18, RuleArgument_list = 19, 
    RuleArgument = 20, RuleMention = 21, RuleMention_attributes = 22, RuleAdditive_numeric_expression = 23, 
    RuleMultiplicative_numeric_expression = 24, RuleSigned_unary_numeric_expression = 25, 
    RuleUnary_numeric_expression = 26, RuleFunction_call = 27, RuleVoid_function_call = 28, 
    RuleSign = 29, RuleVariable_list = 30, RuleCompound_condition_or = 31, 
    RuleCompound_condition_and = 32, RuleNegated_unary_condition = 33, RuleUnary_condition = 34, 
    RuleCondition = 35, RuleConditional_operator = 36, RuleExpression = 37
  };

  explicit ArcscriptParser(antlr4::TokenStream *input);

  ArcscriptParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ArcscriptParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class InputContext;
  class ScriptContext;
  class Script_sectionContext;
  class BlockquoteContext;
  class ParagraphContext;
  class Paragraph_startContext;
  class CodestartContext;
  class CodeendContext;
  class Assignment_segmentContext;
  class Function_call_segmentContext;
  class Conditional_sectionContext;
  class If_sectionContext;
  class Else_if_sectionContext;
  class Else_sectionContext;
  class If_clauseContext;
  class Else_if_clauseContext;
  class Endif_segmentContext;
  class Statement_assignmentContext;
  class Statement_function_callContext;
  class Argument_listContext;
  class ArgumentContext;
  class MentionContext;
  class Mention_attributesContext;
  class Additive_numeric_expressionContext;
  class Multiplicative_numeric_expressionContext;
  class Signed_unary_numeric_expressionContext;
  class Unary_numeric_expressionContext;
  class Function_callContext;
  class Void_function_callContext;
  class SignContext;
  class Variable_listContext;
  class Compound_condition_orContext;
  class Compound_condition_andContext;
  class Negated_unary_conditionContext;
  class Unary_conditionContext;
  class ConditionContext;
  class Conditional_operatorContext;
  class ExpressionContext; 

  class  InputContext : public antlr4::ParserRuleContext {
  public:
    InputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScriptContext *script();
    antlr4::tree::TerminalNode *EOF();
    CodestartContext *codestart();
    Compound_condition_orContext *compound_condition_or();
    CodeendContext *codeend();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InputContext* input();

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Script_sectionContext *> script_section();
    Script_sectionContext* script_section(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptContext* script();

  class  Script_sectionContext : public antlr4::ParserRuleContext {
  public:
    Script_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockquoteContext *> blockquote();
    BlockquoteContext* blockquote(size_t i);
    std::vector<ParagraphContext *> paragraph();
    ParagraphContext* paragraph(size_t i);
    Assignment_segmentContext *assignment_segment();
    Function_call_segmentContext *function_call_segment();
    Conditional_sectionContext *conditional_section();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Script_sectionContext* script_section();

  class  BlockquoteContext : public antlr4::ParserRuleContext {
  public:
    BlockquoteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BLOCKQUOTESTART();
    antlr4::tree::TerminalNode *BLOCKQUOTEEND();
    std::vector<ParagraphContext *> paragraph();
    ParagraphContext* paragraph(size_t i);
    std::vector<Assignment_segmentContext *> assignment_segment();
    Assignment_segmentContext* assignment_segment(size_t i);
    std::vector<Function_call_segmentContext *> function_call_segment();
    Function_call_segmentContext* function_call_segment(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockquoteContext* blockquote();

  class  ParagraphContext : public antlr4::ParserRuleContext {
  public:
    ParagraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Paragraph_startContext *paragraph_start();
    antlr4::tree::TerminalNode *PARAGRAPHEND();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParagraphContext* paragraph();

  class  Paragraph_startContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *paragraphstartToken = nullptr;
    antlr4::Token *bq_paragraphstartToken = nullptr;
    Paragraph_startContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARAGRAPHSTART();
    antlr4::tree::TerminalNode *BQ_PARAGRAPHSTART();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Paragraph_startContext* paragraph_start();

  class  CodestartContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *codestartToken = nullptr;
    antlr4::Token *bq_codestartToken = nullptr;
    CodestartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODESTART();
    antlr4::tree::TerminalNode *BQ_CODESTART();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodestartContext* codestart();

  class  CodeendContext : public antlr4::ParserRuleContext {
  public:
    CodeendContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODEEND();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodeendContext* codeend();

  class  Assignment_segmentContext : public antlr4::ParserRuleContext {
  public:
    Assignment_segmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    Statement_assignmentContext *statement_assignment();
    CodeendContext *codeend();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_segmentContext* assignment_segment();

  class  Function_call_segmentContext : public antlr4::ParserRuleContext {
  public:
    Function_call_segmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    Statement_function_callContext *statement_function_call();
    CodeendContext *codeend();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_call_segmentContext* function_call_segment();

  class  Conditional_sectionContext : public antlr4::ParserRuleContext {
  public:
    Conditional_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    If_sectionContext *if_section();
    Endif_segmentContext *endif_segment();
    std::vector<Else_if_sectionContext *> else_if_section();
    Else_if_sectionContext* else_if_section(size_t i);
    Else_sectionContext *else_section();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conditional_sectionContext* conditional_section();

  class  If_sectionContext : public antlr4::ParserRuleContext {
  public:
    If_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    If_clauseContext *if_clause();
    CodeendContext *codeend();
    ScriptContext *script();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_sectionContext* if_section();

  class  Else_if_sectionContext : public antlr4::ParserRuleContext {
  public:
    Else_if_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    Else_if_clauseContext *else_if_clause();
    CodeendContext *codeend();
    ScriptContext *script();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Else_if_sectionContext* else_if_section();

  class  Else_sectionContext : public antlr4::ParserRuleContext {
  public:
    Else_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    antlr4::tree::TerminalNode *ELSEKEYWORD();
    CodeendContext *codeend();
    ScriptContext *script();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Else_sectionContext* else_section();

  class  If_clauseContext : public antlr4::ParserRuleContext {
  public:
    If_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IFKEYWORD();
    Compound_condition_orContext *compound_condition_or();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_clauseContext* if_clause();

  class  Else_if_clauseContext : public antlr4::ParserRuleContext {
  public:
    Else_if_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSEIFKEYWORD();
    Compound_condition_orContext *compound_condition_or();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Else_if_clauseContext* else_if_clause();

  class  Endif_segmentContext : public antlr4::ParserRuleContext {
  public:
    Endif_segmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodestartContext *codestart();
    antlr4::tree::TerminalNode *ENDIFKEYWORD();
    CodeendContext *codeend();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Endif_segmentContext* endif_segment();

  class  Statement_assignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *variableToken = nullptr;
    Statement_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    Compound_condition_orContext *compound_condition_or();
    antlr4::tree::TerminalNode *ASSIGNADD();
    antlr4::tree::TerminalNode *ASSIGNSUB();
    antlr4::tree::TerminalNode *ASSIGNMUL();
    antlr4::tree::TerminalNode *ASSIGNDIV();
    antlr4::tree::TerminalNode *ASSIGN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Statement_assignmentContext* statement_assignment();

  class  Statement_function_callContext : public antlr4::ParserRuleContext {
  public:
    Statement_function_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Void_function_callContext *void_function_call();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Statement_function_callContext* statement_function_call();

  class  Argument_listContext : public antlr4::ParserRuleContext {
  public:
    Argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_listContext* argument_list();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Additive_numeric_expressionContext *additive_numeric_expression();
    antlr4::tree::TerminalNode *STRING();
    MentionContext *mention();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class  MentionContext : public antlr4::ParserRuleContext {
  public:
    ArcscriptParser::Mention_attributesContext *mention_attributesContext = nullptr;
    std::vector<Mention_attributesContext *> attr;
    MentionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MENTION_TAG_OPEN();
    antlr4::tree::TerminalNode *TAG_CLOSE();
    antlr4::tree::TerminalNode *TAG_OPEN();
    antlr4::tree::TerminalNode *MENTION_TAG_CLOSE();
    antlr4::tree::TerminalNode *MENTION_LABEL();
    std::vector<Mention_attributesContext *> mention_attributes();
    Mention_attributesContext* mention_attributes(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MentionContext* mention();

  class  Mention_attributesContext : public antlr4::ParserRuleContext {
  public:
    Mention_attributesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ATTR_NAME();
    antlr4::tree::TerminalNode *TAG_EQUALS();
    antlr4::tree::TerminalNode *ATTR_VALUE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mention_attributesContext* mention_attributes();

  class  Additive_numeric_expressionContext : public antlr4::ParserRuleContext {
  public:
    Additive_numeric_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicative_numeric_expressionContext *multiplicative_numeric_expression();
    Additive_numeric_expressionContext *additive_numeric_expression();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Additive_numeric_expressionContext* additive_numeric_expression();
  Additive_numeric_expressionContext* additive_numeric_expression(int precedence);
  class  Multiplicative_numeric_expressionContext : public antlr4::ParserRuleContext {
  public:
    Multiplicative_numeric_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Signed_unary_numeric_expressionContext *signed_unary_numeric_expression();
    Multiplicative_numeric_expressionContext *multiplicative_numeric_expression();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicative_numeric_expressionContext* multiplicative_numeric_expression();
  Multiplicative_numeric_expressionContext* multiplicative_numeric_expression(int precedence);
  class  Signed_unary_numeric_expressionContext : public antlr4::ParserRuleContext {
  public:
    Signed_unary_numeric_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SignContext *sign();
    Unary_numeric_expressionContext *unary_numeric_expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Signed_unary_numeric_expressionContext* signed_unary_numeric_expression();

  class  Unary_numeric_expressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *variableToken = nullptr;
    Unary_numeric_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOLEAN();
    Function_callContext *function_call();
    antlr4::tree::TerminalNode *LPAREN();
    Compound_condition_orContext *compound_condition_or();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unary_numeric_expressionContext* unary_numeric_expression();

  class  Function_callContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *fnameToken = nullptr;
    ArcscriptParser::Argument_listContext *argument_listContext = nullptr;
    Function_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FNAME();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Argument_listContext *argument_list();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_callContext* function_call();

  class  Void_function_callContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *vfnameToken = nullptr;
    ArcscriptParser::Argument_listContext *argument_listContext = nullptr;
    antlr4::Token *vfnamevarsToken = nullptr;
    ArcscriptParser::Variable_listContext *variable_listContext = nullptr;
    Void_function_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VFNAME();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Argument_listContext *argument_list();
    antlr4::tree::TerminalNode *VFNAMEVARS();
    Variable_listContext *variable_list();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Void_function_callContext* void_function_call();

  class  SignContext : public antlr4::ParserRuleContext {
  public:
    SignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignContext* sign();

  class  Variable_listContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *variableToken = nullptr;
    Variable_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_listContext* variable_list();

  class  Compound_condition_orContext : public antlr4::ParserRuleContext {
  public:
    Compound_condition_orContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Compound_condition_andContext *compound_condition_and();
    Compound_condition_orContext *compound_condition_or();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *ORKEYWORD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Compound_condition_orContext* compound_condition_or();

  class  Compound_condition_andContext : public antlr4::ParserRuleContext {
  public:
    Compound_condition_andContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Negated_unary_conditionContext *negated_unary_condition();
    Compound_condition_andContext *compound_condition_and();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *ANDKEYWORD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Compound_condition_andContext* compound_condition_and();

  class  Negated_unary_conditionContext : public antlr4::ParserRuleContext {
  public:
    Negated_unary_conditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_conditionContext *unary_condition();
    antlr4::tree::TerminalNode *NEG();
    antlr4::tree::TerminalNode *NOTKEYWORD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Negated_unary_conditionContext* negated_unary_condition();

  class  Unary_conditionContext : public antlr4::ParserRuleContext {
  public:
    Unary_conditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionContext *condition();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unary_conditionContext* unary_condition();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    Conditional_operatorContext *conditional_operator();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  Conditional_operatorContext : public antlr4::ParserRuleContext {
  public:
    Conditional_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NE();
    antlr4::tree::TerminalNode *ISKEYWORD();
    antlr4::tree::TerminalNode *NOTKEYWORD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conditional_operatorContext* conditional_operator();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOLEAN();
    Additive_numeric_expressionContext *additive_numeric_expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool mentionSempred(MentionContext *_localctx, size_t predicateIndex);
  bool additive_numeric_expressionSempred(Additive_numeric_expressionContext *_localctx, size_t predicateIndex);
  bool multiplicative_numeric_expressionSempred(Multiplicative_numeric_expressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace Arcweave
