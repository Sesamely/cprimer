/*************************************************************************
	> File Name: repeatSquare.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月21日 星期二 15时10分49秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
    long int a,b,n,c = 1;
    long int mask = 0x0000000000000001;
    cout << "输入a,b,n" << "\n" << "计算c = a^b mod n" << endl;
    cin >> a >> b >> n;
    if (b == 0)
        c = 1 % n;
    while (b != 0)
    {
        if ((b & mask) == 1) 
            c = (c * a) % n;
        a = (a * a) % n;
        b = b >> 1;
    }
    cout << "c 的值为: " << c << endl;
    return 0;
}
