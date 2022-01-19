#include <iostream>
using namespace std;

enum ASTNodeType 
{
   Undefined,
   OperatorPlus,
   OperatorMinus,
   OperatorMul,
   OperatorDiv,
   UnaryMinus,
   NumberValue
};

class ASTNode
{
public:
   ASTNodeType Type;
   double      Value;
   ASTNode    *Left;
   ASTNode    *Right;
   ASTNode();
   ~ASTNode();
};