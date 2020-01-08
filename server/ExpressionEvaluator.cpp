#include "ExpressionEvaluator.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <stack>
#include <queue>

namespace {
namespace ErrorMessages {

const char INVALID_EXPRESSION[] = "Invalid expression";

} // namespace ErrorMessages

bool isSpace( char ch )
{
    return ch == ' ';
}

bool isOpenParentheses( char ch )
{
    return ch == '(';
}

bool isCloseParentheses( char ch )
{
    return ch == ')';
}

bool isAddOrSub( char ch )
{
    return ch == '+' || ch == '-';
}

bool isMulOrDiv( char ch )
{
    return ch == '*' || ch == '/';
}

bool isOperator( char ch )
{
    return isAddOrSub( ch ) || isMulOrDiv( ch );
}

bool isAllowedOperandCharacter( char ch )
{
    return ( ch >= '0' && ch <= '9' ) || ch == '.';
}

enum OperatorPrecedence
{
    OPERATOR_PRECEDENCE_UNDEFINED = 0,
    OPERATOR_PRECEDENCE_ADD_SUB,
    OPERATOR_PRECEDENCE_MUL_DIV
};

OperatorPrecedence determineOperatorPrecedence( char ch )
{
    if( isAddOrSub( ch ) )
    {
        return OPERATOR_PRECEDENCE_ADD_SUB;
    }
    else if( isMulOrDiv( ch ) )
    {
        return OPERATOR_PRECEDENCE_MUL_DIV;
    }
    return OPERATOR_PRECEDENCE_UNDEFINED;
}

enum TokenType
{
    TOKEN_TYPE_UNDEFINED = 0,
    TOKEN_TYPE_OPEN_PARANTHESES,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_OPERAND
};

struct ExpressionToken
{
    ExpressionToken( const std::string& tokenData,
                     TokenType tokenType,
                     OperatorPrecedence operatorPrecedence
                      = OPERATOR_PRECEDENCE_UNDEFINED ):
        data( tokenData ),
        type( tokenType ),
        precedence( operatorPrecedence )
    {
    }

    std::string data;
    TokenType type;
    OperatorPrecedence precedence;
};

bool equalsZero( double value )
{
    return std::fabs( value - 0.0 )
            < std::numeric_limits< double >::epsilon();
}

bool performOperation( const ExpressionToken& leftOperand,
                       const ExpressionToken& operation,
                       const ExpressionToken& rightOperand,
                       ExpressionToken& result )
{
    const double nLeftOperand = std::atof( leftOperand.data.c_str() );
    const double nRightOperand = std::atof( rightOperand.data.c_str() );
    double nResult = 0.0;

    // TODO: overflow checks ?
    if( operation.data == "+" )
    {
        nResult = nLeftOperand + nRightOperand;
    }
    else if( operation.data == "-" )
    {
        nResult = nLeftOperand - nRightOperand;
    }
    else if( operation.data == "*" )
    {
        nResult = nLeftOperand * nRightOperand;
    }
    else if( operation.data == "/" )
    {
        if( equalsZero( nRightOperand ) )
        {
            result.data = "Expression contains division by zero";
            return false;
        }

        nResult = nLeftOperand / nRightOperand;
    }

    std::stringstream oResultStream;
    oResultStream << std::setprecision(
                         std::numeric_limits< double >::digits10 )
                  << nResult;
    result.data = oResultStream.str();
    return true;
}

} // namespace

namespace tcp_calc {
namespace server {
namespace expression_evaluator {

void evaluateExpression( const std::string& expression,
                         std::string& result )
{
    std::queue< ExpressionToken > oQueue;
    std::stack< ExpressionToken > oStack;

    // convert expression from infix to postfix notation
    //  (or Reverse Polish notation aka RPN)
    {
        for( int i = 0; i < expression.length(); )
        {
            const char& oCharacter = expression[i];

            if( isSpace( oCharacter ) )
            {
                ++i;
                continue;
            }
            else if( isOpenParentheses( oCharacter ) )
            {
                oStack.push( ExpressionToken( std::string( 1, oCharacter ),
                                              TOKEN_TYPE_OPEN_PARANTHESES ) );
            }
            else if( isCloseParentheses( oCharacter ) )
            {
                while( !oStack.empty()
                       && oStack.top().type != TOKEN_TYPE_OPEN_PARANTHESES )
                {
                    ExpressionToken oToken = oStack.top();
                    oStack.pop();
                    oQueue.push( oToken );
                }

                if( !oStack.empty()
                    && oStack.top().type == TOKEN_TYPE_OPEN_PARANTHESES )
                {
                    oStack.pop();
                }
                else
                {
                    result = ErrorMessages::INVALID_EXPRESSION;
                    return;
                }
            }
            else
            {
                OperatorPrecedence precedence
                        = determineOperatorPrecedence( oCharacter );

                if( precedence != OPERATOR_PRECEDENCE_UNDEFINED )
                {
                    // operator
                    ExpressionToken oToken( std::string( 1, oCharacter ),
                                           TOKEN_TYPE_OPERATOR,
                                           precedence );
                    while( !oStack.empty()
                           && oToken.precedence <= oStack.top().precedence )
                    {
                        ExpressionToken oTopToken = oStack.top();
                        oStack.pop();
                        oQueue.push( oTopToken );
                    }

                    oStack.push( oToken );
                }
                else
                {
                    // operand
                    ExpressionToken oToken( "", TOKEN_TYPE_OPERAND );

                    int j = i;
                    for( ; j < expression.length(); ++j )
                    {
                        const char& oSubCharacter = expression[j];

                        if( isOpenParentheses( oSubCharacter )
                            || isCloseParentheses( oSubCharacter )
                            || isOperator( oSubCharacter ) )
                        {
                            break;
                        }

                        if( !isAllowedOperandCharacter( oSubCharacter ) )
                        {
                            std::stringstream oErrorStream;
                            oErrorStream << "Expression '" << expression
                                         << "' contains unsupported character '"
                                         << oSubCharacter << "' at position " << j;
                            result = oErrorStream.str();
                            return;
                        }

                        oToken.data += oSubCharacter;
                    }

                    oQueue.push( oToken );
                    i = j;
                    continue;
                }
            }

            ++i;
        }

        while( !oStack.empty() )
        {
            ExpressionToken token = oStack.top();
            oStack.pop();
            oQueue.push( token );
        }
    }

    if( !oStack.empty() )
    {
        result = ErrorMessages::INVALID_EXPRESSION;
        return;
    }

    ExpressionToken oLeftOperand( "", TOKEN_TYPE_OPERAND );
    ExpressionToken oRightOperand( "", TOKEN_TYPE_OPERAND );

    // evaluate expression in prefix notation
    {
        while( !oQueue.empty() )
        {
            ExpressionToken oToken = oQueue.front();
            oQueue.pop();
            switch( oToken.type )
            {
                case TOKEN_TYPE_OPERAND:
                    oStack.push( oToken );
                    break;
                case TOKEN_TYPE_OPERATOR:
                {
                    if( oStack.size() < 2 )
                    {
                        result = ErrorMessages::INVALID_EXPRESSION;
                        return;
                    }

                    oRightOperand = oStack.top();
                    oStack.pop();
                    oLeftOperand = oStack.top();
                    oStack.pop();
                    ExpressionToken oResultToken( "", TOKEN_TYPE_OPERAND );

                    if( !performOperation( oLeftOperand, oToken,
                                           oRightOperand, oResultToken ) )
                    {
                        result = oResultToken.data;
                        return;
                    }

                    oStack.push( oResultToken );
                    break;
                }
                default:
                    result = ErrorMessages::INVALID_EXPRESSION;
                    return;
            }
        }

        if( oStack.size() != 1 )
        {
            result = ErrorMessages::INVALID_EXPRESSION;
            return;
        }

        result = oStack.top().data;
        oStack.pop();
    }
}

} // namespace expression_evaluator
} // namespace server
} // namespace tcp_calc
