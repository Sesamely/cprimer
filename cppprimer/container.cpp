/************************************************************************
****	> File Name:    	container.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 18 Jan 2018 09:15:24 PM CST
************************************************************************/

#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<forward_list>
#include<array>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main() 
{
    int cnt = 0;
    string s;
    cin >> s;
    cnt = s.length();
    for (auto i : s) {
        cout << (unsigned char)i  << ' ';
    }
    cout << endl;
    ofstream out("./file1", ofstream::out | ofstream::trunc);
    if (out.good()) {
        out << s;
        out << '\n';
    }
    if (out.good()) {
        cout << cnt << endl;
        out.close();
        return 0;
    }
    else {
        return -1;
    }
}
