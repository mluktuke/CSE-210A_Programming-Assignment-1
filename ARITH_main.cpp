#include <iostream>
#include <sstream>
using namespace std;
#include "interpreter.h"
#include "AST.h"
#include "parser.h"

void Test(const char* text)
{
	Parser parser;

	try
	{
		ASTNode* ast = parser.Parse(text);

		try
		{
			Evaluator eval;
			double val = eval.Eval(ast);

			cout << text << " = " << val << endl;
		}
		catch (EvaluatorException& ex)
		{
			cout << text << " t " << ex.what() << endl;
		}

		delete ast;
	}
	catch (ParserException& ex)
	{
		cout << text << " t " << ex.what() << endl;
	}
}
int main()
{
	cout << "The easy test cases: " << endl;
	Test("2 + 3"); //5
	Test("3 + 92"); //95
	Test("100 + 0"); //100
	Test("-1 + -3"); //-4
	Test("10 + -3"); //7
	Test("-1 + 0"); //-1
	Test("99 + 3 + 12 + 2"); //116
	Test("2 + 3 + 4 + -1"); //8
	Test("-1 + -2 + 3"); //0
	Test("-1 + -5 + -1"); //-7
	Test("9 * 3"); //27
	Test("-3 * 4"); //-12
	Test("0 * 2"); //0
	Test("20 * 5"); //100
	Test("0 * 2"); //0
	Test("-2 * -0"); //0
	Test("2 * 3 * 4 * 1000"); //24000
	Test("1 * -2 * 3 * -4"); //24
	Test("9 * 2 * 99 * 999"); //1780218
	Test("1 * 1 * -1 * 1"); //-1
	cout << endl;

	cout << "The medium test cases: " << endl;
	Test("2 + 3 * 4"); //14
	Test("-2 + 3 * -4 + 6 * 2 * 0"); //-14
	Test("3 * 8 + 9 * 10"); //114
	Test("5 * 6 + 9"); //39
	Test("5 * 8 + 6 * 4 + -2"); //62
	Test("-10 * 4 + 3 * 6 + 8"); //-14
	Test("100 + -100 * 0"); //100
	Test("0 * 0 + 0 + -0"); //0
	Test("2 * 4 * -2 + 3 * 8"); //8
	Test("-1 + -0 * 8"); //-1
	cout << endl;

	cout << "Personal test cases: " << endl; //division
	Test("56 / 1"); //56
	Test("2 + 3 / 4"); //2.75
	Test("10 / 10 + 8"); //9
	Test("300 / 10"); //30
	Test("-5 * 8 / 10"); //-4
	cout << endl;

	return 0;
}