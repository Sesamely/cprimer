/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Fri 19 Jan 2018 07:57:37 PM CST
************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<cstring>
#include<iterator>
#include<map>
#include<set>
using namespace std;


int main1(int argv, char **args) 
{
    string word;
    map<string, size_t> word_count;
    set<string> no_string{"fiename", "lyw", "newiyuil@163.com"};
    if (argv < 2) {
        cout << "usage: elfname filename [filename...]" << endl;
        return -1;
    } 
    for (auto i = args+1; i != args + argv; ++i) {
        ifstream in(*i);
        if (!in.good()) {
            cout << "file " << *i << " open failure!" << endl;
            continue;
        }
        while (in >> word) {
            for_each(word.begin(), word.end(), [](char &s){ s = tolower(s); });
            if (no_string.find(word) == no_string.cend()) {
                ++word_count[word];
            }
        }
    }
    
    for (auto wc : word_count) {
        cout << wc.first << " \t\t\t\t\toccurs\t\t " << wc.second << (wc.second > 1 ? " times" : " time") << endl;
    }
    cout << "words number is: " << word_count.size() << endl;
    return 0;
}


int main()
{
    string s("liuyiwemasafsdfsddfafsfca");
    cout << sizeof(s) << endl;
    return 0;
}
