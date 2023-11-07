#include "ArcscriptVisitor.h"
#include "ArcscriptParser.h"

using namespace Arcweave;

std::any ArcscriptVisitor::visitInput(ArcscriptParser::InputContext * ctx)
{
  if (ctx->script() != NULL) {
    return visitScript(ctx->script());
  }
  // Condition
  Expression comp_cond = std::any_cast<Expression>(visitCompound_condition_or(ctx->compound_condition_or()));
  return comp_cond.value;
}

std::any ArcscriptVisitor::visitScript_section(ArcscriptParser::Script_sectionContext *ctx) {
  if (ctx == NULL) {
    return std::any();
  }

  if (ctx->NORMALTEXT().size() > 0) {
    state->outputs.push_back(ctx->getText());
    return ctx->getText();
  }

  return visitChildren(ctx);
}

std::any ArcscriptVisitor::visitAssignment_segment(ArcscriptParser::Assignment_segmentContext *ctx) {
  return visitStatement_assignment(ctx->statement_assignment());
}

std::any ArcscriptVisitor::visitFunction_call_segment(ArcscriptParser::Function_call_segmentContext *ctx) {
  return visitStatement_function_call(ctx->statement_function_call());
}

std::any ArcscriptVisitor::visitConditional_section(ArcscriptParser::Conditional_sectionContext *ctx) {
  ConditionalSection ifSection = std::any_cast<ConditionalSection>(visitIf_section(ctx->if_section()));
  if (ifSection.clause) {
    return ifSection.script;
  }
  for (ArcscriptParser::Else_if_sectionContext *else_if_section : ctx->else_if_section()) {
    ConditionalSection elif_section = std::any_cast<ConditionalSection>(visitElse_if_section(else_if_section));
    if (elif_section.clause) {
      return elif_section.script;
    }
  }
  if (ctx->else_section() != NULL) {
    ConditionalSection elseSection = std::any_cast<ConditionalSection>(visitElse_section(ctx->else_section()));
    return elseSection.script;
  }

  return std::any();
}

std::any ArcscriptVisitor::visitIf_section(ArcscriptParser::If_sectionContext *ctx) {
  Expression result = std::any_cast<Expression>(visitIf_clause(ctx->if_clause()));
  ConditionalSection ifSection;
  ifSection.clause = false;
  if (result == true) {
    ifSection.clause = true;
    ifSection.script = visitScript(ctx->script());
  }
  return ifSection;
}

std::any ArcscriptVisitor::visitElse_if_section(ArcscriptParser::Else_if_sectionContext *ctx) {
  Expression result = std::any_cast<Expression>(visitElse_if_clause(ctx->else_if_clause()));
  ConditionalSection elseSection;
  elseSection.clause = false;
  if (result == true) {
    elseSection.clause = true;
    elseSection.script = visitScript(ctx->script());
  }

  return elseSection;
}

std::any ArcscriptVisitor::visitElse_section(ArcscriptParser::Else_sectionContext *ctx) {
  ConditionalSection elseIfSection;
  elseIfSection.clause = true;
  elseIfSection.script = visitScript(ctx->script());
  return elseIfSection;
}

std::any ArcscriptVisitor::visitIf_clause(ArcscriptParser::If_clauseContext *ctx) {
  return visitCompound_condition_or(ctx->compound_condition_or());
}

std::any ArcscriptVisitor::visitElse_if_clause(ArcscriptParser::Else_if_clauseContext *ctx) {
  return visitCompound_condition_or(ctx->compound_condition_or());
}

std::any ArcscriptVisitor::visitStatement_assignment(ArcscriptParser::Statement_assignmentContext *ctx) {
  std::string variableName = ctx->VARIABLE()->getText();
  Expression compound_condition_or = std::any_cast<Expression>(visitCompound_condition_or(ctx->compound_condition_or()));
  if (ctx->ASSIGN() != NULL) {
    state->setVarValue(variableName, compound_condition_or.value);
    return std::any();
  }

  Expression varValue;
  varValue.setValue(state->getVarValue(variableName));

  if (ctx->ASSIGNADD() != NULL) {
    varValue += compound_condition_or;
  }
  if (ctx->ASSIGNSUB() != NULL) {
    varValue -= compound_condition_or;
  }
  if (ctx->ASSIGNMUL() != NULL) {
    varValue *= compound_condition_or;
  }
  if (ctx->ASSIGNDIV() != NULL) {
    varValue /= compound_condition_or;
  }

  state->setVarValue(variableName, varValue.value);
  return std::any();
}

std::any ArcscriptVisitor::visitCompound_condition_or(ArcscriptParser::Compound_condition_orContext *ctx) {
  std::any cond_any = visitCompound_condition_and(ctx->compound_condition_and());
  Expression compound_condition_and = std::any_cast<Expression>(cond_any);
  if (ctx->compound_condition_or() != NULL) {
    Expression compound_condition_or = std::any_cast<Expression>(visitCompound_condition_or(ctx->compound_condition_or()));
    Expression result(compound_condition_and || compound_condition_or);
    return result;
  }
  return compound_condition_and;
}

std::any ArcscriptVisitor::visitCompound_condition_and(ArcscriptParser::Compound_condition_andContext *ctx) {
  std::any cond_any = visitNegated_unary_condition(ctx->negated_unary_condition());
  Expression negated_unary_condition = std::any_cast<Expression>(cond_any);
  if (ctx->compound_condition_and() != NULL) {
    Expression compound_condition_and = std::any_cast<Expression>(visitCompound_condition_and(ctx->compound_condition_and()));
    Expression result(negated_unary_condition && compound_condition_and);
    return result;
  }
  return negated_unary_condition;
}

std::any ArcscriptVisitor::visitNegated_unary_condition(ArcscriptParser::Negated_unary_conditionContext *ctx) {
  Expression unary_condition = std::any_cast<Expression>(visitUnary_condition(ctx->unary_condition()));
  if (ctx->NEG() != NULL || ctx->NOTKEYWORD() != NULL) {
    return Expression(!unary_condition);
  }
  return unary_condition;
}

std::any ArcscriptVisitor::visitCondition(ArcscriptParser::ConditionContext *ctx) {
  if (ctx->expression().size() == 1) {
    return visitExpression(ctx->expression()[0]);

    // Expression expr = std::any_cast<Expression>(exprAny);
    // if (expr.type() == typeid(double)) {
    //   return expr > 0.0;
    // }
    // else if (expr.type() == typeid(int)) {
    //   return expr > 0;
    // }
    // else if (expr.type() == typeid(std::string)) {
    //   return expr != "";
    // }
    // return std::any_cast<bool>(expr.value);
  }

  ArcscriptParser::Conditional_operatorContext *cond_operator_ctx = ctx->conditional_operator();
  Expression exp0 = std::any_cast<Expression>(visitExpression(ctx->expression()[0]));
  Expression exp1 = std::any_cast<Expression>(visitExpression(ctx->expression()[1]));
  bool result = false;
  if (cond_operator_ctx->GT() != NULL) {
    result = exp0 > exp1;
  }
  else if (cond_operator_ctx->GE() != NULL) {
    result = exp0 >= exp1;
  }
  else if (cond_operator_ctx->LT() != NULL) {
    result = exp0 < exp1;
  }
  else if (cond_operator_ctx->LE() != NULL) {
    result = exp0 <= exp1;
  }
  else if (cond_operator_ctx->EQ() != NULL) {
    result = exp0 == exp1;
  }
  else if (cond_operator_ctx->NE() != NULL) {
    result = exp0 != exp1;
  }
  else if (cond_operator_ctx->ISKEYWORD() != NULL) {
    if (cond_operator_ctx->NOTKEYWORD() != NULL) {
      result = exp0 != exp1;
    } else {
      result = exp0 == exp1;
    }
  }
  return Expression(result);
}

std::any ArcscriptVisitor::visitExpression(ArcscriptParser::ExpressionContext *ctx) {
  if (ctx->STRING() != NULL) {
    std::string result = ctx->STRING()->getText();
    result = result.substr(1, result.size() - 2);
    return Expression(result);
  }
  if (ctx->BOOLEAN() != NULL) {
    return Expression(ctx->BOOLEAN()->getText() == "true");
  }

  return visitAdditive_numeric_expression(ctx->additive_numeric_expression());
}

std::any ArcscriptVisitor::visitAdditive_numeric_expression(ArcscriptParser::Additive_numeric_expressionContext *ctx) {
  Expression mult_num_expr = std::any_cast<Expression>(visitMultiplicative_numeric_expression(ctx->multiplicative_numeric_expression()));
  if (ctx->additive_numeric_expression() != NULL) {
    Expression result = std::any_cast<Expression>(visitAdditive_numeric_expression(ctx->additive_numeric_expression()));
    if (ctx->ADD() != NULL) {
      mult_num_expr = mult_num_expr + result;
    }
    else if (ctx->SUB() != NULL) {
      mult_num_expr = mult_num_expr - result;
    }
  }
  return mult_num_expr;
}

std::any ArcscriptVisitor::visitMultiplicative_numeric_expression(ArcscriptParser::Multiplicative_numeric_expressionContext *ctx) {
  Expression signed_unary_num_expr = std::any_cast<Expression>(visitSigned_unary_numeric_expression(ctx->signed_unary_numeric_expression()));
  if (ctx->multiplicative_numeric_expression() != NULL) {
    Expression result = std::any_cast<Expression>(visitMultiplicative_numeric_expression(ctx->multiplicative_numeric_expression()));
    if (ctx->MUL() != NULL) {
      signed_unary_num_expr = signed_unary_num_expr * result;
    }
    else if (ctx->DIV() != NULL) {
      signed_unary_num_expr = signed_unary_num_expr / result;
    }
  }

  return signed_unary_num_expr;
}

std::any ArcscriptVisitor::visitSigned_unary_numeric_expression(ArcscriptParser::Signed_unary_numeric_expressionContext *ctx) {
  std::any expr_any = visitUnary_numeric_expression(ctx->unary_numeric_expression());
  Expression unary_num_expr = std::any_cast<Expression>(expr_any);
  ArcscriptParser::SignContext *sign = ctx->sign();

  if (sign != NULL) {
    if (sign->ADD() != NULL) {
      return unary_num_expr;
    }
    // Else MINUS
    unary_num_expr = unary_num_expr * (-1);
  }
  return unary_num_expr;
}

std::any ArcscriptVisitor::visitUnary_numeric_expression(ArcscriptParser::Unary_numeric_expressionContext *ctx) {
  if (ctx->FLOAT() != NULL) {
    Expression result(std::stod(ctx->FLOAT()->getText()));
    return result;
  }
  if (ctx->INTEGER() != NULL) {
    Expression result(std::stoi(ctx->INTEGER()->getText()));
    return result;
  }
  if (ctx->VARIABLE() != NULL) {
    std::string variableName = ctx->VARIABLE()->getText();
    std::any varValue = state->getVarValue(variableName);
    if (varValue.type() == typeid(std::string)) {
      Expression result(std::any_cast<std::string>(varValue));
      return result;
    }
    if (varValue.type() == typeid(bool)) {
      Expression result(std::any_cast<bool>(varValue));
      return result;
    }
    if (varValue.type() == typeid(int)) {
      Expression result(std::any_cast<int>(varValue));
      return result;
    }
    if (varValue.type() == typeid(double)) {
      Expression result(std::any_cast<double>(varValue));
      return result;
    }
  }
  if (ctx->function_call() != NULL) {
    std::any resultValue = visitFunction_call(ctx->function_call());
    if (resultValue.type() == typeid(std::string)) {
      Expression result(std::any_cast<std::string>(resultValue));
      return result;
    }
    if (resultValue.type() == typeid(bool)) {
      Expression result(std::any_cast<bool>(resultValue));
      return result;
    }
    if (resultValue.type() == typeid(int)) {
      Expression result(std::any_cast<int>(resultValue));
      return result;
    }
    if (resultValue.type() == typeid(double)) {
      Expression result(std::any_cast<double>(resultValue));
      return result;
    }
    throw Arcweave::RuntimeErrorException("Unknown result type from function call: " + ctx->function_call()->getText() + "\nType: " + resultValue.type().name());
  }
  return visitCompound_condition_or(ctx->compound_condition_or());
}

std::any ArcscriptVisitor::visitVoid_function_call(ArcscriptParser::Void_function_callContext *ctx) {
  std::string fname = "";
  std::any result;
  if (ctx->VFNAME() != NULL) {
    fname = ctx->VFNAME()->getText();
    std::vector<std::any> argument_list_result;
    if (ctx->argument_list() != NULL) {
      argument_list_result = std::any_cast<std::vector<std::any>>(visitArgument_list(ctx->argument_list()));
    }
    result = functions->Call(fname, argument_list_result);
  }

  if (ctx->VFNAMEVARS() != NULL) {
    fname = ctx->VFNAMEVARS()->getText();
    std::vector<std::any> variable_list_result;

    if (ctx->variable_list() != NULL) {
      variable_list_result = std::any_cast<std::vector<std::any>>(visitVariable_list(ctx->variable_list()));
    }
    result = functions->Call(fname, variable_list_result);
  }
  // std::any result = std::invoke(functions->functions[fname], functions, argument_list_result);
  
  return result;
}

std::any ArcscriptVisitor::visitFunction_call(ArcscriptParser::Function_callContext *ctx) {
  std::vector<std::any> argument_list_result;
  if (ctx->argument_list() != NULL) {
    argument_list_result = std::any_cast<std::vector<std::any>>(visitArgument_list(ctx->argument_list()));
  }
  std::string fname = ctx->FNAME()->getText();

  // std::any result = std::invoke(functions->functions[fname], functions, argument_list_result);
  std::any result = functions->Call(fname, argument_list_result);
  return result;
}

std::any ArcscriptVisitor::visitVariable_list(ArcscriptParser::Variable_listContext *ctx) {
  std::vector<std::any> variables;
  for (antlr4::tree::TerminalNode *variable : ctx->VARIABLE()) {
    variables.push_back(state->getVar(variable->getText()));
  }
  return variables;
}

std::any ArcscriptVisitor::visitArgument_list(ArcscriptParser::Argument_listContext *ctx) {
  std::vector<std::any> arguments;
  for (ArcscriptParser::ArgumentContext *argument : ctx->argument()) {
    arguments.push_back(visitArgument(argument));
  }
  return arguments;
}

std::any ArcscriptVisitor::visitArgument(ArcscriptParser::ArgumentContext *ctx) {
  if (ctx->STRING() != NULL) {
    std::string result = ctx->STRING()->getText();
    result = result.substr(1, result.size() - 2);
    return Expression(result);
  }
  if (ctx->mention() != NULL) {
    Mention mention_result = std::any_cast<Mention>(visitMention(ctx->mention()));
    return mention_result;
  }

  return visitAdditive_numeric_expression(ctx->additive_numeric_expression());
}

std::any ArcscriptVisitor::visitMention(ArcscriptParser::MentionContext *ctx) {
  std::map<std::string, std::string> attrs;
  for (ArcscriptParser::Mention_attributesContext *attr : ctx->mention_attributes()) {
    std::map<std::string, std::string> res = std::any_cast<std::map<std::string, std::string>>(visitMention_attributes(attr));
    attrs[res["name"]] = res["value"];
  }
  std::string label = "";
  if (ctx->MENTION_LABEL() != NULL) {
    label = ctx->MENTION_LABEL()->getText();
  }
  Mention mention(label, attrs);
  return mention;
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::any ArcscriptVisitor::visitMention_attributes(ArcscriptParser::Mention_attributesContext *ctx) {
  std::string name = ctx->ATTR_NAME()->getText();
  antlr4::tree::TerminalNode *valueNode = ctx->ATTR_VALUE();
  std::string value(name);
  
  if (valueNode != NULL) {
    std::string strvalue = valueNode->getText();
    if ((strvalue.rfind("\"", 0) == 0 && ends_with(strvalue, "\"")) ||
         strvalue.rfind("'", 0) == 0 && ends_with(strvalue, "'")) {
      
      strvalue = strvalue.substr(1, strvalue.size() - 2);
      
    }
    value = strvalue;
  }
  return std::map<std::string, std::string> { {"name", name }, {"value", value } };
}