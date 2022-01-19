#include <iostream>
#include <sstream>
using namespace std;
#include "AST.h"

enum TokenType 
{
   Error,
   Plus,
   Minus,
   Mul,
   Div,
   EndOfText,
   OpenParenthesis,
   ClosedParenthesis,
   Number
};

struct Token 
{
   TokenType	Type;
   double		Value;
   char		Symbol;

   Token():Type(Error), Value(0), Symbol(0)
   {}
};

class Parser
{
   Token m_crtToken;
   const char* m_Text;
   size_t m_Index;

private:
   ASTNode* Expression();
   ASTNode* Expression1();
   ASTNode* Term();
   ASTNode* Term1();
   ASTNode* Factor();
   ASTNode* CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right);
   ASTNode* CreateUnaryNode(ASTNode* left);
   ASTNode* CreateNodeNumber(double value);
   void Match(char expected);
   void SkipWhitespaces();
   void GetNextToken();
   double GetNumber();
public:
   ASTNode* Parse(const char* text);
};