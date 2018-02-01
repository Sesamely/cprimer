/************************************************************************
****	> File Name:    	matrix_chain_order.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 31 Jan 2018 03:46:09 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void matrix_chain_order(const vector<int> &p,
                       vector<vector<int>> &m,
                       vector<vector<int>> &s)
{    
    int len = p.size()-1,
        i,
        j,
        cur_len,
        k;
    m.reserve(len+1); s.reserve(len+1);

    for (i=0; i<=len; ++i ) {
        m[i].reserve(len+1);
        s[i].reserve(len+1);
        m[i][i] = 0;
    }

    for (cur_len=2 ; cur_len<=len; ++cur_len) {
        for (i=1; i<=len-cur_len+1; ++i) {
            j = i + cur_len - 1;
                 
            int min = ~(1<<31);
            for (k=i; k<j; ++k) {
                int temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (temp < min) {
                    min = temp;
                    s[i][j] = k;
                }
            }
            m[i][j] = min;
        }
    }
}

void print_s(const vector<vector<int>> &s, int i, int j)
{
    if (i==j) {
        cout << " A" << i << " ";
    }
    else {
        cout << "(";
        print_s(s, i, s[i][j]);
        print_s(s, s[i][j]+1, j);
        cout << ")";
    }
}

int main()
{
    int i;
    vector<vector<int>> m, s;
    vector<int> p;
    while(cin >> i) p.push_back(i);
    matrix_chain_order(p, m, s);

    print_s(s, 1, p.size()-1);
    cout << endl;
    return 0;
}

