/************************************************************************
****	> File Name:    	test2.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月10日 星期六 14时29分55秒
************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    int i = 0x1312423;
    string s;
    ostringstream os;
    os << i;
    s = os.str();
    istringstream is(s);
    is >> i;
    for (const auto &c : s) cout << c << " ";
    cout << endl;
    cout << i << endl;

    return 0;
}
