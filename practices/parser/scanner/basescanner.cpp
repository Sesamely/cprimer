#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<vector>
using namespace std;
/*declaration*/
void getToken(ifstream& in);
/*global variables*/
unsigned int ROW,CNT;
string operators = "+ - \\ * / = % : | , > _ < (){}[] \" ' ;";
char c = ' ';

int main(int argv,char **args)
{
    int count = 3;
    string filename;
    ifstream in;
/*提示用户输入文件名字,并打开文件*/
    while(count>0&&count<=3) {/*{{{*/
        if(args[1] == NULL || count <3) {
            cout << "\n请输入文件名:\n>" ;
            getline(cin,filename);
        }
        else {
            filename = args[1];
        }
        in.open(filename.c_str());
        if(!in) {
            if (count != 1)
            cout << "ERROR!!!\n打开文件出错，请从新输入文件名,还有" << count-1 << "次机会"<<endl;
        }
        else break;
        count--;
    }
    if(!in) {
        cout << "文件没有打开!!!" << endl;
        return 1;
    }/*}}}*/
/*文件打开后的操作*/
    ROW = CNT = 1;
    while(!in.eof()) {
        getToken(in);
    }
    return 0;
}
void getToken(ifstream& in)/*{{{*/
{
    string str= "";
    int  flag = 1;
    int  tmp  = -1;
/*除去不可见字符，若其中有'\n'则调整行数ROW和个数CNT,若到达结尾退出*/
    while(isspace(c)) {
        if(in.eof()) return;  /*如果到达文件结尾,退出*/
        if (c == '\n') {
            ROW += 1;
            CNT= 1;
        }
        in.read(&c,1);
    }
/*判断是什么类型的token*/
    if(isdigit(c)) {
        do {
            if(c == '.') {
                flag = 0;
            }
            str += c;
            in.read(&c,1);
        }while(isdigit(c)||(c=='.'&&flag==1));
        tmp = 1;
    }
    else if(isalpha(c)) {
        do {
            str += c;
            in.read(&c,1);
        }while(isalnum(c));
        tmp = 2;
    }
    else if(operators.find(c)!=string::npos){
        tmp = 4;
        str += c;
        in.read(&c,1);
    }
/*判断是否有错误，若有错则报错*/
    if (!isspace(c)&&operators.find(c)==string::npos&&tmp!=4) {
        do {
            str += c;
            in.read(&c,1);
        }while(!isspace(c));
        printf("\e[1;31m第%4d行第%4d个nekot出错 >>>>>> 出错的nekot是%s\n\e[0m", \
                    ROW,CNT,str.c_str());
    }
/*无错情况，对不同类型token分别处理*/
    else {
        switch (tmp) {
            case 1:
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是 number : "<<  \
                     strtod(str.c_str(),NULL) <<endl;
                break;
            case 2:
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是identify: "<<str<<endl;
                break;
            default:;
        }
    }
    if(tmp!=4) CNT++;
}/*}}}*/
