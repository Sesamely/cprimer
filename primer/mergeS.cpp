/************************************************************************
****	> File Name:    	mergeS.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 01:29:25 AM CST
************************************************************************/

#include<iostream>
#include<string>
#include<memory>
using namespace std;

//shared_ptr<char>
char* mergeS(const char* s1, const char* s2) {

    int len1=0, len2=0, i=0;
    while (s1[++len1] != '\0');
    while (s2[++len2] != '\0');

    char *p = new char[len1+len2+1], *temp=p;
    for (; i < len1; ++i) {
        *temp++ = s1[i];
    }
    for (; i < len1 + len2; ++i) {
        *temp++ = s2[i-len1];
    }
    *temp = '\0';
    return p;
}

char* mergeS(const string& str1, const string& str2) {
    
    int len1 = str1.length(), len2 = str2.length(), i = 0;
    char *p = new char[len1+len2+1], *temp=p;
    for (; i < len1; ++i) {
        *temp++ = str1[i];
    }
    for (; i < len1 + len2; ++i) {
        *temp++ = str2[i-len1];
    }
    *temp = '\0';
    return p;

}

int main(int argc, char **argv) 
{
    if (argc != 3) {
        cout << "usage: elf string1 string2" << endl;
        return -1;
    }
    string s1(argv[1]);
    string s2(argv[2]);
    //char *p = mergeS(argv[1], argv[2]);
    char *p = mergeS(s1, s2);
    cout << p << endl;
    delete [] p;

    return 0;
}
