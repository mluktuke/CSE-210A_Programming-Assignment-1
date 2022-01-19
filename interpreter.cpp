#include <iostream>
#include <sstream>
using namespace std;
#include "interpreter.h"

class EvaluatorException : public exception
{
public:
   EvaluatorException(const string& message):
      exception(message.c_str())
    {
    }
};

double eval(ASTNode* ast)
{
    if(ast == NULL) 
    {
        stringstream str;
        str << "Invalid input!";
        throw EvaluatorException(str.str());
    }
    if(ast->Type == NumberValue)
        return ast->Value;
    else if(ast->Type == UnaryMinus)
        return -eval(ast->Left);
    else 
    {
        double e1 = eval(ast->Left);
        double e2 = eval(ast->Right);
        switch(ast->Type)
        {
        case OperatorPlus:  
            return e1 + e2;
        case OperatorMinus: 
            return e1 - e2;
        case OperatorMul:   
            return e1 * e2;
        case OperatorDiv:   
            return e1 / e2;
        }
    }
    stringstream str1;
    str1 << "Invalid syntax tree!";
    throw EvaluatorException(str1.str());
   }

double Eval(ASTNode* ast)
{
    if(ast == NULL)
    {
        stringstream str2;
        str2 << "Invalid abstract syntax tree!";
        throw EvaluatorException(str2.str());
    }

    return eval(ast);
}