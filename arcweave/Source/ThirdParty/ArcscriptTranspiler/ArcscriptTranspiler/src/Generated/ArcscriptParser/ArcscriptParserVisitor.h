
// Generated from ArcscriptParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "ArcscriptParser.h"


namespace Arcweave {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by ArcscriptParser.
 */
class  ArcscriptParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ArcscriptParser.
   */
    virtual std::any visitInput(ArcscriptParser::InputContext *context) = 0;

    virtual std::any visitScript(ArcscriptParser::ScriptContext *context) = 0;

    virtual std::any visitScript_section(ArcscriptParser::Script_sectionContext *context) = 0;

    virtual std::any visitAssignment_segment(ArcscriptParser::Assignment_segmentContext *context) = 0;

    virtual std::any visitFunction_call_segment(ArcscriptParser::Function_call_segmentContext *context) = 0;

    virtual std::any visitConditional_section(ArcscriptParser::Conditional_sectionContext *context) = 0;

    virtual std::any visitIf_section(ArcscriptParser::If_sectionContext *context) = 0;

    virtual std::any visitElse_if_section(ArcscriptParser::Else_if_sectionContext *context) = 0;

    virtual std::any visitElse_section(ArcscriptParser::Else_sectionContext *context) = 0;

    virtual std::any visitIf_clause(ArcscriptParser::If_clauseContext *context) = 0;

    virtual std::any visitElse_if_clause(ArcscriptParser::Else_if_clauseContext *context) = 0;

    virtual std::any visitEndif_segment(ArcscriptParser::Endif_segmentContext *context) = 0;

    virtual std::any visitStatement_assignment(ArcscriptParser::Statement_assignmentContext *context) = 0;

    virtual std::any visitStatement_function_call(ArcscriptParser::Statement_function_callContext *context) = 0;

    virtual std::any visitArgument_list(ArcscriptParser::Argument_listContext *context) = 0;

    virtual std::any visitArgument(ArcscriptParser::ArgumentContext *context) = 0;

    virtual std::any visitMention(ArcscriptParser::MentionContext *context) = 0;

    virtual std::any visitMention_attributes(ArcscriptParser::Mention_attributesContext *context) = 0;

    virtual std::any visitAdditive_numeric_expression(ArcscriptParser::Additive_numeric_expressionContext *context) = 0;

    virtual std::any visitMultiplicative_numeric_expression(ArcscriptParser::Multiplicative_numeric_expressionContext *context) = 0;

    virtual std::any visitSigned_unary_numeric_expression(ArcscriptParser::Signed_unary_numeric_expressionContext *context) = 0;

    virtual std::any visitUnary_numeric_expression(ArcscriptParser::Unary_numeric_expressionContext *context) = 0;

    virtual std::any visitFunction_call(ArcscriptParser::Function_callContext *context) = 0;

    virtual std::any visitVoid_function_call(ArcscriptParser::Void_function_callContext *context) = 0;

    virtual std::any visitSign(ArcscriptParser::SignContext *context) = 0;

    virtual std::any visitVariable_list(ArcscriptParser::Variable_listContext *context) = 0;

    virtual std::any visitCompound_condition_or(ArcscriptParser::Compound_condition_orContext *context) = 0;

    virtual std::any visitCompound_condition_and(ArcscriptParser::Compound_condition_andContext *context) = 0;

    virtual std::any visitNegated_unary_condition(ArcscriptParser::Negated_unary_conditionContext *context) = 0;

    virtual std::any visitUnary_condition(ArcscriptParser::Unary_conditionContext *context) = 0;

    virtual std::any visitCondition(ArcscriptParser::ConditionContext *context) = 0;

    virtual std::any visitConditional_operator(ArcscriptParser::Conditional_operatorContext *context) = 0;

    virtual std::any visitExpression(ArcscriptParser::ExpressionContext *context) = 0;


};

}  // namespace Arcweave
