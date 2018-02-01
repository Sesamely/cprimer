/************************************************************************
****	> File Name:    	parlindrome.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 01 Feb 2018 01:16:50 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
void max_parlindrome(const vector<T> &s, vector<vector<int>> &m)
{
    int i, j;
    const int last = s.size()-1, first = 0;
    m.reserve(s.size());
    for (i=first; i<=last; ++i ) {
        m[i].reserve(s.size());
        m[i][i] = 1;
        if (i) m[i][i-1] = 0;
    }
    
    for (j=first+1; j<=last; ++j) {
        for (i=j-1; i>=first; --i) {
            if (s[i] == s[j]) {
                m[i][j] = m[i+1][j-1] + 1;
            }
            else if (m[i][j-1] >= m[i+1][j]) {
                m[i][j] = m[i][j-1];
            }
            else m[i][j] = m[i+1][j];
        }
    }
}

template <typename T>
void print_parlindrome(const vector<T> &s,
                       const vector<vector<int>> &m, int i, int j)
{
    if (i>j) return;

    if (m[i][j] == 1) {
        if (j!=0 && m[i][j-1] == 1) {
            cout << s[i] << " ";
        }
        cout << s[i] << " ";
        return;
    }

    if (m[i][j] == m[i][j-1]) {
        print_parlindrome<T>(s, m, i, j-1);
    }
    else if(m[i][j] == m[i+1][j] ) {
        print_parlindrome<T>(s, m, i+1, j);
    }
    else if (m[i][j] == m[i+1][j-1] + 1 ) {
        cout << s[i] << ' ';
        print_parlindrome<T>(s, m, i+1, j-1);
        cout << s[i] << ' ';
    }
}

void disp_vector_m(vector<vector<int>> &m)
{
    const int row_last = m.capacity()-1,
                col_last = m[0].capacity() -1;
    int i, j;
    for (i=0; i<= row_last; ++i) {
        for (j=0; j<=col_last; ++j) {
            if (i>j) cout << " " << " ";
            else cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    string str;
    char type_var;
    vector<vector<int>> m;
    vector<char> s;
    
    while (cin >> type_var) {
        s.push_back(type_var);
    }

    max_parlindrome(s, m);

    cout << "max parlindrome length is: " << m[0][s.size()-1] 
        << "\n\t" << "parlindrome sequence is : ";
    print_parlindrome(s, m, 0, s.size()-1);
    cout << endl;

    /*disp_vector_m(m);*/

    return 0;
}



