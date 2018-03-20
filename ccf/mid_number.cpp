/************************************************************************
****	> File Name:    	mid_number.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月17日 星期六 14时55分00秒
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
            i++;
            if (i!=j) swap(v[i], v[j]);
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
    int n;
    cin >> n;
    vector<int> v;
    v.reserve(n);
    int temp_i;
    for (int i=0; i<n; ++i) {
        cin >> temp_i;
        v.push_back(temp_i);
    }

    quick_sort(v, 0, n-1);

    int mid_number = v[n/2];

    int small_cnt = 0, big_cnt = 0;

    for (int i=0; i<n; ++i) {
        if (v[i] < mid_number)
            ++small_cnt;
        if (v[i] > mid_number)
            ++big_cnt;
    }

    if (small_cnt == big_cnt)
        cout << mid_number << endl;
    else cout << -1 << endl;

    return 0;
}
