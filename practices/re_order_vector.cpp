/************************************************************************
****	> File Name:    	re_order_vector.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 05 Feb 2018 10:53:38 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool judge(const vector<int> &vec, int loc) {
    if (vec[loc] & 1) return true;
    return false;
}
int reorder_vector(vector<int> &vec)
{
    int begin = 0, end = vec.size()-1;

    int base = vec[end];

    while (begin < end) {
        while (begin < end && vec[begin]<=base)
            ++begin;
        while (begin < end && vec[end]>=base)
            --end;
        if (begin < end) 
            swap(vec[begin], vec[end]);
    }
    swap(vec[begin], vec[vec.size()-1]);

    return begin;
}

int main() {
    int i;
    vector<int> v;
    while(cin >> i) v.push_back(i);

    cout << v[reorder_vector(v)] << endl;

    for (const auto &i : v) cout << i << " "; cout << endl;

    return 0;
}
