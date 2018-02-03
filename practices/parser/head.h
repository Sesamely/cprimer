/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月28日 星期四 00时12分09秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<vector>
#include<map>
#include<typeinfo>
using namespace std;
/*costomizeType*/
enum TokenType{
    tok_id = 1,
    tok_num = 2,
    tok_op = 3,
    tok_eof = -1,
    tok_err = 0
};
class ExprAST {
public:
    virtual ~ExprAST() {}
};
class NumberExpr : public ExprAST {
public:
    double value;
    NumberExpr(double val) : value(val) {}
};
class VariableExprAST : public ExprAST {
public:
    string Name;
    VariableExprAST(const string &name) : Name(name) {}
};
class BinaryExprAST : public ExprAST {
public:
    char op;
    ExprAST *LHS,*RHS;
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) :
    op(op),LHS(lhs),RHS(rhs) {}
};
/*class CallExprAST : public ExprAST {
}*/

/*globalVariable*/
#ifndef EXTERN
#define EXTERN extern
#endif
EXTERN string Identifier;
EXTERN char Operator;
EXTERN double Number;
EXTERN ifstream in;
EXTERN unsigned int ROW,CNT;
EXTERN TokenType CurrentToken;
EXTERN map<char, int> BinopPrecedence;
EXTERN char reg_number ;


/*prototype*/
/*parser.cpp*/
static ExprAST *paresrIdentifier();
static ExprAST *parserExpression();
static TokenType getToken(ifstream &in);
static void initGlobal();
static TokenType getNextToken();

/*lib.cpp*/
#ifndef _LIB_
void disp();
void dispExpressPre(ExprAST *node);
void dispExpressMid(ExprAST *node);
void dispExpressPost(ExprAST *node);
int maxDepthOf(ExprAST *node);
void printPretty(ExprAST *root, int level, int indentSpace, ostream& out);
#endif

#endif     
