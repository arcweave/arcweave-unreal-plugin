
// Generated from ArcscriptParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "ArcscriptParserVisitor.h"


namespace Arcweave {

/**
 * This class provides an empty implementation of ArcscriptParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ArcscriptParserBaseVisitor : public ArcscriptParserVisitor {
public:

  virtual std::any visitInput(ArcscriptParser::InputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScript(ArcscriptParser::ScriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScript_section(ArcscriptParser::Script_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_segment(ArcscriptParser::Assignment_segmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_call_segment(ArcscriptParser::Function_call_segmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_section(ArcscriptParser::Conditional_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_section(ArcscriptParser::If_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElse_if_section(ArcscriptParser::Else_if_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElse_section(ArcscriptParser::Else_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_clause(ArcscriptParser::If_clauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElse_if_clause(ArcscriptParser::Else_if_clauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEndif_segment(ArcscriptParser::Endif_segmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement_assignment(ArcscriptParser::Statement_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement_function_call(ArcscriptParser::Statement_function_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_list(ArcscriptParser::Argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(ArcscriptParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMention(ArcscriptParser::MentionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMention_attributes(ArcscriptParser::Mention_attributesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditive_numeric_expression(ArcscriptParser::Additive_numeric_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicative_numeric_expression(ArcscriptParser::Multiplicative_numeric_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSigned_unary_numeric_expression(ArcscriptParser::Signed_unary_numeric_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_numeric_expression(ArcscriptParser::Unary_numeric_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_call(ArcscriptParser::Function_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVoid_function_call(ArcscriptParser::Void_function_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSign(ArcscriptParser::SignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_list(ArcscriptParser::Variable_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompound_condition_or(ArcscriptParser::Compound_condition_orContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompound_condition_and(ArcscriptParser::Compound_condition_andContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegated_unary_condition(ArcscriptParser::Negated_unary_conditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_condition(ArcscriptParser::Unary_conditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(ArcscriptParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_operator(ArcscriptParser::Conditional_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(ArcscriptParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Arcweave
