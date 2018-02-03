/*************************************************************************
	> File Name: stringMatch.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年01月04日 星期四 13时47分54秒
 ************************************************************************/

//模式第一位与后面所有位都不一样

#include<iostream>
#include<string>
using namespace std;

string T = "liuyiwen1231242323534534123223432";

bool match(const string &P,const string &T,unsigned &s)/*{{{*/
{
    unsigned long j=0;
    while (j < P.length()) {
        if(T[s] == P[j]) {
            s++;
            j++;
        }
        else break;
    }
    if (j >= P.length()) {
        return true;
    }
    else {
        return false;
    }
}/*}}}*/
bool match2(const string &P,const string &T,unsigned s)
{
    string dispString;
    unsigned long j=0;
    while (j < P.length() && s < T.length()) {
        if(T[s] == P[j]) {
            dispString += T[s];
            s++;
            j++;
        }
        else if (P[j] == '_') {
            while(j < P.length() && P[j]=='_') j++;
            if (j>=P.length()) {
                while (s < T.length()) {
                    dispString += T[s];
                    s++;
                }
                cout << "Match string is :" << dispString ;
                return true;
            }
            //此处改进
            while(true) {
                while (T[s] != P[j] && s<T.length()) dispString += T[s++];
                if (s>=T.length()) break;
                bool flag = false;
                unsigned temp = s+1;
                for (;temp<T.length();temp++) {
                    if(T[temp] == P[j]) flag = true;
                }
                if (!flag) break;
                else s++;
            }
        }
        else {
            break;
        } 
    }
    while(j < P.length() && P[j]=='_') j++;
    if (j >= P.length()) {
        cout << "Match string is :" << dispString ;
        return true;
    }
    else {
        return false;
    }
}
void stringMatch(const string &P,const string &T)/*{{{*/
{
    if (T.length() < P.length()) {
        cout << "Pattern's length is larger than the Text's" << endl;
        return ;
    }
    unsigned i=0;
    while (i <= T.length() - P.length()) {
        unsigned temp = i;
        if (match(P, T, i)) {
            cout << "match s is " << temp << " -> match string is :";
            unsigned k=0;
            for (; k<P.length(); k++) {
                cout << T[temp+k] ;
            }
            cout << endl;
        }
        if (T[i] != P[0]) i++;
    }
}/*}}}*/
void stringMatch2(const string &P,const string &T)
{
    unsigned cnt = 0, i = 0;
    for (;i<P.length();i++) if (P[i] == '_') cnt++;
    if (T.length() < P.length() - cnt) {
        cout << "Pattern's length is larger than the Text's" << endl;
        return ;
    }
    i = 0;
    while (i <= T.length()) {
        if (match2(P, T, i)) {
            cout << "\tmatch s is " << i << endl;
        }
        i++;
    }
}
int main(int argc, char **args) 
{
    if (argc == 1) {
        cout << "Usage: stringMatch stringP {stringT}" << endl;
        return -1;
    }
    if (argc == 3) {
        T = args[2];
    }
    cout << "T is "<< T << endl;
    cout << "P is "<< args[1] << endl;
    stringMatch2(args[1], T);
    return 0;
}

