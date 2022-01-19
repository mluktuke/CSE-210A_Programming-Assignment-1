#include <iostream>
#include <sstream>
using namespace std;
#include "parser.h"

ASTNode* Parser::Expression()
{
    ASTNode* tnode = Term();
    ASTNode* e1node = Expression1();

    return CreateNode(OperatorPlus, tnode, e1node);
}   

ASTNode* Parser::Expression1()
{
    ASTNode* tnode;
    ASTNode* e1node;

    switch(m_crtToken.Type)
    {
    case Plus:
        GetNextToken();
        tnode = Term();
        e1node = Expression1();

        return CreateNode(OperatorPlus, e1node, tnode);

    case Minus:
        GetNextToken();
        tnode = Term();
        e1node = Expression1();

        return CreateNode(OperatorMinus, e1node, tnode);
    }

    return CreateNodeNumber(0);
}

ASTNode* Parser::Term()
{
    ASTNode* fnode = Factor();
    ASTNode* t1node = Term1();

    return CreateNode(OperatorMul, fnode, t1node);
}

ASTNode* Parser::Term1()
{
    ASTNode* fnode;
    ASTNode* t1node;

    switch(m_crtToken.Type)
    {
    case Mul: 
        GetNextToken();
        fnode = Factor();
        t1node = Term1();
        return CreateNode(OperatorMul, t1node, fnode);

    case Div:
        GetNextToken();
        fnode = Factor();
        t1node = Term1();
        return CreateNode(OperatorDiv, t1node, fnode);
    }

    return CreateNodeNumber(1);
   }

ASTNode* Parser::Factor()
{
    ASTNode* node;
    switch(m_crtToken.Type)
    {
    case Minus:
        GetNextToken();
		node = Factor();
        return CreateUnaryNode(node);

    case Number:
    {
        double value = m_crtToken.Value;
        GetNextToken();
        return CreateNodeNumber(value);
    }

    default:
    {
        stringstream sstr; 
        sstr << "Unexpected token '" << m_crtToken.Symbol << "' at position " << m_Index;
        throw ParserException(sstr.str(), m_Index);
    }
    }
}

ASTNode* Parser::CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right)
{
    ASTNode* node = new ASTNode;
    node->Type = type;
    node->Left = left;
    node->Right = right;

    return node;
}

ASTNode* Parser::CreateUnaryNode(ASTNode* left)
{
    ASTNode* node = new ASTNode;
    node->Type = UnaryMinus;
    node->Left = left;
    node->Right = NULL;

    return node;
}

ASTNode* Parser::CreateNodeNumber(double value)
{
    ASTNode* node = new ASTNode;
    node->Type = NumberValue;
    node->Value = value;

    return node;
}

void Parser::Match(char expected)
{
    if(m_Text[m_Index-1] == expected)
        GetNextToken();
    else
    {
        stringstream sstr;
        sstr << "Expected token '" << expected << "' at position " << m_Index;
        throw ParserException(sstr.str(), m_Index);
    }
}

void Parser::SkipWhitespaces()
{
    while(isspace(m_Text[m_Index])) m_Index++;
}

void Parser::GetNextToken()
{
    SkipWhitespaces();

	m_crtToken.Value = 0;
	m_crtToken.Symbol = 0;

    if(m_Text[m_Index] == 0)
    {
        m_crtToken.Type = EndOfText;
        return;
    }

    if(isdigit(m_Text[m_Index]))
    {
        m_crtToken.Type = Number;
		m_crtToken.Value = GetNumber();
        return;
    }

    m_crtToken.Type = Error;

    switch(m_Text[m_Index])
    {
    case '+': m_crtToken.Type = Plus; break;
    case '-': m_crtToken.Type = Minus; break;
    case '*': m_crtToken.Type = Mul; break;
    case '/': m_crtToken.Type = Div; break;
    }

    if(m_crtToken.Type != Error)
	{
        m_crtToken.Symbol = m_Text[m_Index];
        m_Index++;
	}
    else
    {
        stringstream sstr; 
        sstr << "Unexpected token '" << m_Text[m_Index] << "' at position " << m_Index;
        throw ParserException(sstr.str(), m_Index);
    }
}

double Parser::GetNumber()
{   
    SkipWhitespaces();

    int index = m_Index;
    while(isdigit(m_Text[m_Index])) m_Index++;
    if(m_Text[m_Index] == '.') m_Index++;
    while(isdigit(m_Text[m_Index])) m_Index++;

    if(m_Index - index == 0)
        throw ParserException("Number expected but not found!", m_Index);

    char buffer[32] = {0};
    memcpy(buffer, &m_Text[index], m_Index - index);

    return atof(buffer);
}

ASTNode* Parser::Parse(const char* text)
{
    m_Text = text;
    m_Index = 0;
    GetNextToken();

    return Expression();
}