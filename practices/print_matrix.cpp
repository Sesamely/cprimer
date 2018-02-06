/************************************************************************
****	> File Name:    	print_matrix.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Tue 06 Feb 2018 02:11:27 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_matrix(const vector<vector<int>> &v, int row_begin, int row_end,
                    int col_begin, int col_end) 
{
    int i = row_begin, j = col_begin;

    if (row_begin > row_end || col_begin > col_end) return;
/*
 *    if (row_begin == row_end) {
 *        for (; j<=col_end; ++j) cout << v[i][j] << " ";
 *        return;
 *    }
 *    if (col_begin == col_end) {
 *        for (; i<=row_end; ++i) cout << v[i][j] << " ";
 *        return;
 *    }
 *
 */

    for (; j<=col_end; ++j) cout << v[i][j] << " ";
    --j; ++i;
    for (; i<=row_end; ++i) cout << v[i][j] << " ";
    --i; --j;
    for (; j>=col_begin; --j) cout << v[i][j] << " ";
    ++j; --i;
    for (; i>=row_begin+1; --i) cout << v[i][j] << " ";

    cout << endl;
    print_matrix(v, row_begin+1, row_end-1, col_begin+1, col_end-1);
}

int main()
{
    int i, row=0;
    vector<vector<int>> v;
    v.push_back(vector<int>());
    while (cin >> i) {
        if (!i) {
            ++row;
            v.push_back(vector<int>());
            continue;
        }
        v[row].push_back(i);
    }

    print_matrix(v, 0, v.size()-1, 0, v[0].size()-1);
    cout << endl;

    return 0;
}
