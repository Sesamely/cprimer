/************************************************************************
****	> File Name:    	ir.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 27 Jan 2018 10:02:33 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void ir(vector<int> &v, int sz) {
    if (sz == 0) return;
    ir(v, sz-1);
    int i = sz-1;
    while (i>=0 && v[i] > v[i+1]) {
        int temp = v[i];
        v[i] = v[i+1];
        v[i+1] = temp;
        --i;
    }
}
void irD(vector<int> &v) {
    if (v.size() < 2) return;
    unsigned int i = 1;
    for (; i<v.size(); ++i) {
        int key = v[i];
        int j = i ;
        while (j>0 && v[j-1] < key) {
            v[j] = v[j-1];
            --j;
        }
        v[j] = key;
        for(const auto &i:v) cout << i << ' '; cout << endl;
    }
}
int main() 
{
    int integer;
    vector<int> a;
    while (cin >> integer) {
        a.push_back(integer);
    }
    irD(a);
    for (const auto &i : a) {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}
