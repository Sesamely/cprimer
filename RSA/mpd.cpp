/*************************************************************************
	> File Name: mpd.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月21日 星期二 15时39分18秒
 ************************************************************************/

#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    long int p,s1,q1,s2,q2;
    cout << "输入一个不太大的合数(两个素数相乘)\n\t将尽可能将其分解为两个素数(不确定是素数)" << endl;
    cin >> p ;
    s2 = s1 = (long int)sqrt(p);
    q1 = q2 = p / s2;
    while(s1 > 0 && q1 * s1 != p && q2 * s2 != p)
    {
        s1--;
        s2++;
        q1 = p / s1;
        q2 = p / s2;
        cout << ". ";
    }
    if (s1 < 0) 
        cout << "error" <<endl;
    else if (q1 * s1 == p)
        cout << p << " = " << s1 << " * " << q1 <<endl;
    else if (q2 * s2 == p)
        cout << p << " = " << s2 << " * " << q2 <<endl;
    return 0;    
}
