/************************************************************************
****	> File Name:    	distribute_cake.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月16日 星期五 15时02分56秒
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &v, int begin, int end)
{
    int last = v[end];
    int i=begin-1, j=begin;
    for (; j<=end; ++j) {
        if (v[j] <= last) {
            ++i;
            if (i != j) swap(v[i], v[j]);
        }
    }

    return i;
}

void quick_sort(vector<int> &v, int begin, int end)
{
    if (begin >= end) return;
    
    int p = partition(v, begin, end);

    quick_sort(v, begin, p-1);
    quick_sort(v, p+1, end);
}


int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> v;
    int i;
    while (cin >> i) v.push_back(i);

    //quick_sort(v, 0, v.size()-1);

    int number = 0;
    int sum = 0;
    for (int i=0; i<n; ++i) {
        sum += v[i];
        if (sum >= k) {
            sum = 0;
            ++number;
        }
    }
    if (sum != 0) ++number;
    cout << number << endl;

    return 0;
}
