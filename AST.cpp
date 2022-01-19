#include <iostream>
using namespace std;
#include "AST.h"

ASTNode::ASTNode()
{
    Type = Undefined;
    Value = 0;
    Left = NULL;
    Right = NULL;
}

ASTNode::~ASTNode()
{
    delete Left;
    delete Right;
}