#include <iostream>
#include <sstream>
using namespace std;
#include "AST.h"
#include "parser.h"

class Evaluator 
{
   double eval(ASTNode* ast);
public:
   double Eval(ASTNode* ast);
};