/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 09:46:31 PM CST
************************************************************************/


#include <iostream>
#include <ctime>
#include <typeinfo>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string s("12425235");
    for_each(s.cbegin(), s.cend(), [](const char &i){cout << (int)i-48 << " ";});
    cout << endl;
    return 0;
}
