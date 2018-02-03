/************************************************************************
****	> File Name:    	lcs_length.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 31 Jan 2018 08:27:52 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;


template <typename T>
void lcs_length(const vector<T> &s1,
                const vector<T> &s2,
                vector<vector<int>> &c)
{
    int i, j,
        row = s1.size() - 1,
        col = s2.size() - 1;
    c.reserve(row+2);
    for (i=0; i<=row+1; ++i) {
        c[i].reserve(col+2);
        if (i) c[i][0] = 0;
        else {
            for (j=0; j<=col+1; ++j) c[i][j] = 0;
        }
    }

    for (i=0; i<=row; ++i) {
        for (j=0; j<=col; ++j) {
            if (s1[i] == s2[j]) {
                c[i+1][j+1] = c[i][j] + 1;
            }
            else if (c[i][j+1] >= c[i+1][j]) {
                c[i+1][j+1] = c[i][j+1];
            }
            else c[i+1][j+1] = c[i+1][j];
        }
    }
}

template <typename T>
void print_lcs(const vector<vector<int>> &c,
               const vector<T> s,
               unsigned i, unsigned j)
{
    if (i==0 || j==0) return ;
    if (c[i][j] == c[i-1][j-1] + 1) {
        print_lcs<T>(c, s, i-1, j-1);
        cout << s[i-1] << ' ';
    }
    else if (c[i][j]==c[i-1][j]) {
        print_lcs<T>(c, s, i-1, j);
    }
    else if (c[i][j] == c[i][j-1]) {
        print_lcs<T>(c, s, i, j-1);
    }
}

#define TYPENAME int
int main()
{
    TYPENAME type_var;
    string str;
    vector<vector<int>> c_result;
    vector<TYPENAME> s1, s2;
    while (cin >> str ) {
        if (str == "!") break;
        type_var = stoi(str);
        s1.push_back(type_var);
    }
    while (cin >> str) {
        type_var = stoi(str);
        s2.push_back(type_var);
    }

    lcs_length<TYPENAME>(s1, s2, c_result);
    cout << "lcs_length is: " << setw(4) << left << c_result[s1.size()][s2.size()]
        << "One of the Sequence is: ";
    print_lcs<TYPENAME>(c_result, s1, s1.size(), s2.size());
    cout << endl;
    return 0;
}
