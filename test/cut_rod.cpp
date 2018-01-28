/************************************************************************
****	> File Name:    	cut_rod.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 27 Jan 2018 09:22:56 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int cut_rod(vector<int> p, int n)
{
    if (n==0) return 0;
    int q=-1;
    for (int i=0; i++!=n; ) {
        int temp = p[i] + cut_rod(p, n-i);
        q = q > temp ? q : temp;
    }
    return q;
}

int main()
{
    vector<int> p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n;
    cin >> n;
    cout << cut_rod(p, n) << endl;

    return 0;
}
