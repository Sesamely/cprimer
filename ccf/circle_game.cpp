/************************************************************************
****	> File Name:    	circlr_game.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 01 Mar 2018 06:28:43 PM CST
************************************************************************/

#include <iostream>
#include <list>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    list<int> li;
    int i;
    long m=1;
    for (i=1; i<=n; ++i) {
        li.push_back(i);
    }
    while (li.size() > 1) {
        i = li.front();
        li.pop_front();
        if (m%k != 0 && m%10 != k)
            li.push_back(i);
        ++m;
    }
    if (li.size() == 1) cout << li.front() << endl;

    return 0;
}
