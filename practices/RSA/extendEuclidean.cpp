/*************************************************************************
	> File Name: extendEuclidean.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月21日 星期二 14时50分56秒
 ************************************************************************/

#include<stdio.h>
#include<iostream>
using namespace std;

int extendEuclidean(long int a,long int p);

int main()
{
    long int result,a,p;
    cout << "输入素数P和a属于[0,P-1](例如：17 5)" << endl;
    cout << "\t求a^(-1) mod P" << endl;
    cin >> p >> a;
    result = extendEuclidean(a,p);
    cout << "a^(-1)mod P 的值为: " << result << endl;
    return 0;
}

int extendEuclidean(long int a,long int p)
{
    int u,v,x1,x2,q,r,x;
    u = ((a%p) + p) % p;
    v = p;
    x1 = 1;
    x2 = 0;
    while (u != 1)
    {
        q = v / u;
        r = v - q * u;
        x = x2 - q * x1;
        x2 = x1;
        x1 = x;
        v = u;
        u = r;
    }
    return ((x1%p + p) % p);
}
