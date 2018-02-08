/************************************************************************
****	> File Name:    	first_only_char.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 07 Feb 2018 09:40:27 PM CST
************************************************************************/

#include <iostream>
#include <string>
#include <map>
using namespace std;

char find_first(string s) {
    int i;
    int hash_table[256];
    for (i=0; i<256; ++i) hash_table[i] = 0;

    for (const auto &c : s) {
        ++hash_table[static_cast<int>(c)];
    }   

    for (i=0; i<256; ++i) {
        if (hash_table[i] == 1) return i;
    }
    return '\0';
}

char find_first1(string s) {
    map<char, int> c_i;
    for (const auto &c : s) {
        ++c_i[c];
    }
    for (const auto &p : c_i) {
        if (p.second == 1) return p.first;
    }
    return '\0';
}

int main()
{
    string s;
    cin >> s;
    cout << find_first1(s) << endl;

    return 0;
}
