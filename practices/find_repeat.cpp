/************************************************************************
****	> File Name:    	find_repeat.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 07 Feb 2018 02:58:22 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int find_repeat(vector<int> &v)
{
    int i=0, last_loc=v.size()-1;
    for (; i<=last_loc; ) {
        if (v[i]==i) ++i;
        else if (v[i] == v[v[i]]) return v[i];
        else swap(v[i], v[v[i]]);
    for (const auto &a:v) cout << a << " "; cout << endl;
    }
    return -1;
}

int main()
{
    int i;
    cin >> i;
    vector<int> v;
    srand(time(nullptr));
    for(int j=0; j<i; ++j) v.push_back(rand()%i);
    //for(int j=0; j<i; ++j) v.push_back(j);

    cout << find_repeat(v) << endl;

    return 0;
}
