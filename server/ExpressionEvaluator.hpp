#pragma once
#ifndef TCPCALC_SERVER_EXPRESSIONEVALUATOR_HPP
#define TCPCALC_SERVER_EXPRESSIONEVALUATOR_HPP

#include <string>

namespace tcp_calc {
namespace server {
namespace expression_evaluator {

/**
 * @brief evaluateExpression Evaluates simple math expression.
 *  Supported operations: + - * / ( )
 * @param expression Expression to evaluate
 * @param result Evaluation result
 */
void evaluateExpression( const std::string& expression,
                         std::string& result );

} // expression_evaluator
} // namespace server
} // namespace tcp_calc

#endif // TCPCALC_SERVER_EXPRESSIONEVALUATOR_HPP
