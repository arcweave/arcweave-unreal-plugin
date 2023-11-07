#pragma once

#include "antlr4-runtime.h"
#include "ArcscriptParserBaseVisitor.h"
#include "ArcscriptFunctions.h"

using namespace Arcweave;

class ArcscriptVisitor : public ArcscriptParserBaseVisitor {
public:
  struct ConditionalSection {
    bool clause;
    std::any script;
  };

  ArcscriptState *state;
  ArcscriptFunctions *functions;

  ArcscriptVisitor(ArcscriptState* _state) : state(_state) {
    functions = new ArcscriptFunctions(state);
  }

  std::any visitInput(ArcscriptParser::InputContext *ctx) override;
  std::any visitScript_section(ArcscriptParser::Script_sectionContext *ctx) override;
  std::any visitAssignment_segment(ArcscriptParser::Assignment_segmentContext *ctx) override;
  std::any visitFunction_call_segment(ArcscriptParser::Function_call_segmentContext * ctx) override;
  std::any visitConditional_section(ArcscriptParser::Conditional_sectionContext *ctx) override;
  std::any visitIf_section(ArcscriptParser::If_sectionContext *ctx) override;
  std::any visitElse_if_section(ArcscriptParser::Else_if_sectionContext *ctx) override;
  std::any visitElse_section(ArcscriptParser::Else_sectionContext *ctx) override;
  std::any visitIf_clause(ArcscriptParser::If_clauseContext *ctx) override;
  std::any visitElse_if_clause(ArcscriptParser::Else_if_clauseContext *ctx) override;
  std::any visitStatement_assignment(ArcscriptParser::Statement_assignmentContext *ctx) override;
  std::any visitCompound_condition_or(ArcscriptParser::Compound_condition_orContext *ctx) override;
  std::any visitCompound_condition_and(ArcscriptParser::Compound_condition_andContext *ctx) override;
  std::any visitNegated_unary_condition(ArcscriptParser::Negated_unary_conditionContext *ctx) override;
  std::any visitCondition(ArcscriptParser::ConditionContext *ctx) override;
  std::any visitExpression(ArcscriptParser::ExpressionContext *ctx) override;
  std::any visitAdditive_numeric_expression(ArcscriptParser::Additive_numeric_expressionContext *ctx) override;
  std::any visitMultiplicative_numeric_expression(ArcscriptParser::Multiplicative_numeric_expressionContext *ctx) override;
  std::any visitSigned_unary_numeric_expression(ArcscriptParser::Signed_unary_numeric_expressionContext *ctx) override;
  std::any visitUnary_numeric_expression(ArcscriptParser::Unary_numeric_expressionContext *ctx) override;
  std::any visitVoid_function_call(ArcscriptParser::Void_function_callContext *ctx) override;
  std::any visitFunction_call(ArcscriptParser::Function_callContext *ctx) override;
  std::any visitVariable_list(ArcscriptParser::Variable_listContext *ctx) override;
  std::any visitArgument_list(ArcscriptParser::Argument_listContext *ctx) override;
  std::any visitArgument(ArcscriptParser::ArgumentContext *ctx) override;
  std::any visitMention(ArcscriptParser::MentionContext *ctx) override;
  std::any visitMention_attributes(ArcscriptParser::Mention_attributesContext *ctx) override;
};