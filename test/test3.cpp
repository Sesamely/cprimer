/************************************************************************
****	> File Name:    	test3.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月20日 星期二 00时55分54秒
************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
    wstring wstr;
    const wchar_t *wc_str;

    wcin >> wstr;
    wc_str = wstr.c_str();

    cout << hex << showbase;
    for (; *wc_str != '\0'&&*(wc_str + 1)!='\0'; ++wc_str) {
        cout << (unsigned int)(unsigned char)*wc_str << " ";
    }
    cout << dec << noshowbase << endl;
    cout << endl;
    cout  << wstr.length() << endl;
    for (auto a : wstr) wcout << a << " "; cout << endl;

    return 0;
}
