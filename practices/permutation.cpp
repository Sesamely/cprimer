/************************************************************************
****	> File Name:    	permutation.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Tue 06 Feb 2018 10:06:42 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
int number=0;

int min(int a, int b, int c) {
    return a < b ? a<c ? a : c : b<c ? b : c;
}
int min2(int a, int b, int c) {
    if (a < b) {
        if (a < c) return a;
        else return c;
    }
    else {
        if (c > b) return b;
        else return c;
    }
}
void disp_all_permutation_of(vector<int> &v, int begin, int end)
{
    if (begin == end) {
        for (const auto &a : v) cout << a << " "; 
        cout << endl;
        //cout << "\t"<< min2(v[0],v[1],v[2]) << endl; //test for min
    }
    for (int i = begin; i<=end; ++i) {
        swap(v[begin], v[i]);
        disp_all_permutation_of(v, begin+1, end);
        swap(v[begin], v[i]);
    }
}
int main()
{
    vector<int> v;
    int i;
    while (cin >> i) v.push_back(i);
    disp_all_permutation_of(v, 0, v.size()-1);
    return 0;
}

void disp_for_queen(const vector<int> &v) {/*{{{*/
    int len = v.size();
    cout << " ";
    for (int i=0; i<len; ++i) cout << " " << i; cout << endl;
    for (int i=0; i<len; ++i) {
        cout << i << " ";
        for (int j=0; j<len; ++j) {
            if (v[i] == j) cout << "◉ ";
            else cout << "+ ";
        }
        cout << endl;
    }
    cout << endl;
}
void queen_8(vector<int> &v, int begin, int end)
{
    if (begin == end) {
        bool flag = true;
        for (int i=0; i<=end; ++i) {
            for (int j=i; j<=end; ++j) {
                if (j!=i)
                    if ((i-j == v[i]-v[j])||(j-i == v[i] - v[j]))
                        flag = false;
                if (!flag) break;
            }
            if(!flag) break;
        }
        if (flag) {
            //disp_for_queen(v);
            ++number;
        }
    }
    for (int i = begin; i<=end; ++i) {
        swap(v[begin], v[i]);
        queen_8(v, begin+1, end);
        swap(v[begin], v[i]);
    }
}
int main1()
{
    int n;
    cin >> n;
    vector<int> v;
    for (int i=0; i<n; ++i) v.push_back(i);

    number = 0;
    queen_8(v, 0, n-1);

    cout << "number is: " << number << endl;
    return 0;
}/*}}}*/
