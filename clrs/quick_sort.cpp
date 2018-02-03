/************************************************************************
****	> File Name:    	quick_sort.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Tue 30 Jan 2018 07:21:25 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

pair<int, int> partion_repeat(vector<int> &v,
                            int begin, int end)
{
    int key = v[end];
    swap(v[begin], v[end]);
    int i = begin - 1,
        k = begin,
        j = begin + 1;
    for (; j<=end; ++j) {
        if (v[j] < key) {
            ++i;
            ++k;
            swap(v[i], v[j]);
            swap(v[k], v[j]);
        } 
        else if (v[j] == key) {
            ++k;
            swap(v[k], v[j]);
        }
    } 
    return {i+1, k};
}

int partion(vector<int> &v, int begin, int end)
{
    int i = begin-1,
        j,
        key = v[end];
    for (j = begin; j<=end; ++j) {
        if (v[j] < key) {
            i++;
            swap(v[i], v[j]);
        }
    }
    /*cout << "\t" << i+1 << "\t";*/
    swap(v[i+1], v[end]);
    /*for (j=begin; j<=end; ++j) cout << v[j] << " "; cout << endl;*/
    return i+1;
}

void quick_sort(vector<int> &v, int begin, int end) {
    if (begin < end) {
        /*
         *pair<int, int> p = partion_repeat(v, begin, end);
         *for (int i=p.first; i<=p.second; ++i) cout << v[i] << ' '; cout << "\n\n";
         *quick_sort(v, begin, p.first-1);
         *quick_sort(v, p.second+1, end);
         */
        int p = partion(v, begin, end);
        quick_sort(v, begin, p-1);
        quick_sort(v, p+1, end);
    }
}

int main()
{
    int temp;
    vector<int> v; v.reserve(100);
    while(cin >> temp) v.push_back(temp); 

    quick_sort(v, 0, v.size()-1);
    for (const auto &i : v) cout << i << ' '; cout << endl;

    return 0;
}
