#define EXTERN
#include "head.h"

/*
 *[>global variables<]
 *ifstream in;
 *unsigned int ROW,CNT;
 *string operators = "+ - \\ * / = % : | , > _ < (){}[] \" ' ;";
 *char CurrentChar = ' ';
 *string Identifier;[>记录当前的标识<]
 *double Number;[>记录当前的数字<]
 *char Operator;[>记录当前的操作符号<]
 *map<char, int> BinopPrecedence;
 *TokenType CurrentToken;
 */

char CurrentChar = ' ';
string operators = "+ - \\ * / = % : | , > _ < (){}[] \" ' ;";
TokenType  getToken(ifstream& in)/*{{{*/
{
    string str= "";
    int  flag = 1;
    TokenType  type = tok_err;
/*除去不可见字符，若其中有'\n'则调整行数ROW和个数CNT,若到达结尾退出*/
    while(isspace(CurrentChar)) {
        if(in.eof()) return tok_eof;  /*如果到达文件结尾,退出*/
        if (CurrentChar == '\n') {
            ROW += 1;
            CNT= 1;
        }
        in.read(&CurrentChar,1);
    }
/*判断是什么类型的token*/
    if(isdigit(CurrentChar)) {
        do {
            if(CurrentChar == '.') {
                flag = 0;
            }
            str += CurrentChar;
            in.read(&CurrentChar,1);
        }while(isdigit(CurrentChar)||(CurrentChar=='.'&&flag==1));
        type = tok_num;
    }
    else if(isalpha(CurrentChar)) {
        do {
            str += CurrentChar;
            in.read(&CurrentChar,1);
        }while(isalnum(CurrentChar));
        type = tok_id;
    }
    else if(operators.find(CurrentChar)!=string::npos){
        type = tok_op;
        str += CurrentChar;
        in.read(&CurrentChar,1);
    }
/*判断是否有错误，若有错则报错*/
    if (!isspace(CurrentChar) && operators.find(CurrentChar)==string::npos && type!=tok_op) {
        do {
            str += CurrentChar;
            in.read(&CurrentChar,1);
        }while(!isspace(CurrentChar));
        printf("\e[1;31m第%4d行第%4d个nekot出错 >>>>>> 出错的nekot是%s\n\e[0m", \
                    ROW,CNT,str.c_str());
    }
/*无错情况，对不同类型token分别处理*/
    else {
        initGlobal();
        switch (type) {
            case tok_id: Identifier = str; break;
            case tok_num: Number = strtod(str.c_str(), 0); break;
            case tok_op: Operator = str[0]; break;
            default:;
        }
    }
    if(type!=tok_op) CNT++;
    return type;
}
/*获得下一个token,同时可能改变Identifier,Number,Operator*/
TokenType getNextToken() {
    return CurrentToken = getToken(in);
}/*}}}*/
/*依据当前读入的Operator决定优先级*//*{{{*/
int GetTokenPrecedence() {
    if (!isascii(Operator) && CurrentToken==tok_op) {
        return -1;
    }
    int TokPrec = BinopPrecedence[Operator];
    if (TokPrec <= 0) return -1;
    return TokPrec;
}

/*错误类型*/
ExprAST * Error(const char *str) {fprintf(stderr,"Error: %s\n",str); return 0;}

/*解析数字*/
ExprAST *parserNumberExpr()
{
    ExprAST *Result = new NumberExpr(Number);
    getNextToken();
    return Result;
}

/*解析标识符*/
ExprAST *parserIdentifier()
{
    ExprAST *Result = new VariableExprAST(Identifier);
    getNextToken();
    return Result;
}

/*解析(expression)*/
ExprAST *parserParenExpr()
{
    getNextToken();
    ExprAST *e = parserExpression();
    if(!e) return 0;
    
    if(Operator != ')')
        return Error("\e[31mExpected ')' in ParenExpr!\e[0m");
    getNextToken();
    return e;
}
/*对以上的数字,标示符,带括号表达解析函数进行封装*/
ExprAST *parserPrime()
{
    ExprAST *Result = NULL;
    switch(CurrentToken) {
        case tok_eof: break;
        case tok_id: Result = parserIdentifier(); break;
        case tok_num: Result = parserNumberExpr(); break;
        case tok_op: {
            switch (Operator) {
                case '(': Result = parserParenExpr();break;
                default:Result = Error("\033[31munknow opretor when expecting '('\033[0m");
            }
        }break;
        default: Result = Error("\033[31munknow token when expecting an expression\033[0m");
    }
    return Result;
}
/*解析二元运算表达式,以下两个函数都是*/
ExprAST *parserBinOpRHS(int ExprPrec, ExprAST *LHS)
{
    while(1) {
        int TokPrec = GetTokenPrecedence();
        if(TokPrec < ExprPrec){
            if(!LHS) cout << "LHS is NULL" << endl;
            return LHS;
        }
        char BinOp = Operator;
        getNextToken();

        ExprAST *RHS = parserPrime();
        if(!RHS) return 0;

        int NextPrec = GetTokenPrecedence();
        if (TokPrec < NextPrec) {
            RHS = parserBinOpRHS(TokPrec+1, RHS);
            if(!RHS) return 0;
        }
        LHS = new BinaryExprAST(BinOp,LHS,RHS);
    }
}
ExprAST *parserExpression()
{
    ExprAST *LHS = parserPrime();
    if (!LHS) return 0;
    
    LHS = parserBinOpRHS(0, LHS);
    /*
     *if(LHS) {
     *    cout << "...I have parser a Expression,next is the tree...\n" << endl;
     *    printPretty(LHS,1,0,cout);
     *    cout << "...END...\n" << endl;
     *}
     *else {
     *    cout << "\e[31mERROR: when I except a expression...\e[0m" << endl;
     *}
     */
    return LHS;
}
/* 解析if-else 样例为：'if n = 0 then 1 else n * y' */
ExprAST *parserIfElse()
{
    ExprAST *temp=NULL;
    getNextToken(); //Eat the 'if'

    cout << "\e[34mif\n\t\e[0m" ;
    if((temp=parserExpression())==NULL)
        return Error("\e[31mExpecting 'statement' in if ->statement then statement else statement\e[0m");
    printPretty(temp,3,5,cout);

    if (Identifier.compare("then"))
        return Error("\e[31mExpecting 'then' in if statement ->then statement else statement\e[0m");
    cout << "\e[34mthen\n\t\e[0m" ;
    getNextToken();

    if ((temp=parserExpression())==NULL) 
        return Error("\e[31mExpecting 'statement' in if statement then ->statement else statement\e[0m");
    printPretty(temp,3,5,cout);
    if (Identifier.compare("else")) 
        return Error("\e[31mExpecting 'else' in if statement then statement ->else statement\e[0m");
    cout << "\e[34melse\n\t\e[0m" ;
    getNextToken();
    if ((temp=parserExpression())==NULL) 
        return Error("\e[31mExpecting 'statement' in if statement then statement else ->statement\e[0m");
    printPretty(temp,3,5,cout);

    return 0; 
}/*}}}*/
/*{{{*//*未完成的函数parser*/
/*
 *fun factorial 0 = 1
 *   | factorial n = n * factorial (n - 1)
 */
ExprAST *parserFunc()
{
    return NULL;
}
/*}}}*/
/*辅助函数*//*{{{*/
void initGlobal()
{
    Number = 0;
    Operator = ' ';
    Identifier = "";
}/*}}}*/
/*初始化map,打开文件*//*{{{*/
int initialize()
{
    string filename = "./test.txt";
    /*
     *cout << ">>>请输入要分析的文件名字: " << "\n\t>" ; 
     *getline(cin,filename);
     */
    in.open(filename);
    if(!in) {
        cout << "\e[31mError open " << filename << "\e[0m" << endl;
        exit(-1);
    }
    BinopPrecedence['='] = 1;
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
    BinopPrecedence['/'] = 40;
    return 0;
}/*}}}*/

int main()
{
    ExprAST *root = NULL;
    initialize();
    getNextToken(); 
    //root = parserIfElse();
    while(!in.eof()) {
        switch(CurrentToken){
            case tok_id:{
                if(!Identifier.compare("if")) {
                    cout << "\e[31m.....IF-ELSE statement start......\e[0m\n" << endl;
                    root = parserIfElse();
                    cout << "\e[31m.....END......\e[0m\n\n" << endl; 
                }
                else {
                    root = parserExpression();
                    cout << "\e[31mI have parsered a Expression, next is .......\e[0m\n" << endl;
                    printPretty(root,1,0,cout);
                    cout << "\e[31m......END.......\e[0m\n\n" << endl; 
                }
            }break;
            case tok_op: {
                if (Operator==';') getNextToken();
            }
            default:;
        } 
    }
    return 0;
}
