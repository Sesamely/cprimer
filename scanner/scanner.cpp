/*************************************************************************
	> File Name: scanner.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月22日 星期三 14时53分25秒
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<vector>
using namespace std;

/*proto*/
void init_keywords();
void getToken(fstream& in);

/*enum*/
enum TOKENTYPE {
    tok_eof    = -1,
    tok_id     = -2,
    tok_number = -3,
    tok_operator_N = -32,
    tok_kw_N = -64
};

/*struct*/
 typedef struct token {
     int id ;
     double number;
     string id_kw;
 }TOKEN;

/*global variable*/
static string operatormap = "{}[]:|''\"^()\\?,>=+-/*_";
vector<string> keywords;
TOKEN gnumber;
TOKEN gidentifyd;
TOKEN gkeyword;
unsigned long int ROW;
unsigned long int CNT;
char c = ' ';


int main(int argv,char **args)
{
    int count = 3;
    string filename;
    fstream in;
    /*提示用户输入文件名字*/
    while(count>0&&count<=3) {
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
    }
    /*文件打开后的操作*/
    init_keywords();
    ROW = CNT = 1;
    while(!in.eof()) {
        getToken(in);
    }
    return 0;
}

void init_keywords()
{
    string filename = "./keyword.inc";
    string ktemp;
    fstream f_in(filename.c_str());
    while (f_in >> ktemp) {
        keywords.insert(keywords.end(),ktemp);
    }
}

void dispKeywords()
{ 
    vector<string>::iterator it = keywords.begin();
    while (it != keywords.end()) {
        cout << *it++ << ' ';    
    }
    cout << endl;
}

void getToken(fstream& in)
{
    string str="";
    int  flag = 1;
    int  tmp  = -1;
/*判断是什么类型的token*/
    do {
        if (in.eof()) break;
        if (c == '\n') {
            ROW += 1;
            CNT= 1;
        }
        in.read(&c,1);
    }while(isspace(c));
    if(in.eof()) return;

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
        for (string kw : keywords) {
            if (str.compare(kw)==0) {
                tmp = 3;
            } 
        }
    }
    else if(operatormap.find(c)!=string::npos){
        tmp = 4;
        str += c;
    }
/*处理*/
    /*有错情况*/
    if (!isspace(c)&&operatormap.find(c)==string::npos&&tmp!=4) {
        do {
            str += c;
            in.read(&c,1);
        }while(!isspace(c));
        cout << "\033[1;31m";
        printf("第%4ld行第%4ld个token出错>>>>出错的token是%s\n\033[0m", \
                    ROW,CNT,str.c_str());
    }
    /*无错情况*/
    else {
        switch (tmp) {
            case 1:
                gnumber.number = strtod(str.c_str(),NULL);
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是  number: "<<gnumber.number<<endl;
                break;
            case 2:
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是identify: "<<str<<endl;
                break;
            case 3:
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是 keyword: "<<str<<endl;
                break;
            case 4:
                cout <<"第"<<setw(4)<<ROW <<"行"  \
                     <<"第"<<setw(4)<<CNT<<"个token是operator: "<<str<<endl;
                break;
            default:;
        }
    }
    CNT++;
    return ;
}

