/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 09:46:31 PM CST
************************************************************************/


#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n, i, temp;
    cin >> n;
    vector<int> v, distance; 
    v.reserve(n); distance.reserve(n);
    for (i=0; i<n; ++i) {
        cin >> temp;
        v.push_back(temp);
    }
    sort(v.begin(), v.end());

    for (i=0; i<n-1; ++i) {
        int abs = v[i+1] - v[i];
        if (abs < 0) abs = -abs;
        distance.push_back(abs);
    }
    int min = ~(1<<31);
    for (const auto &i : distance) 
        cout << i << " ";
        if (i < min) min = i;

    cout << min << endl;
    return 0;
}
