/************************************************************************
****	> File Name:    	ugly_number.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 07 Feb 2018 04:04:08 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int min(int a, int b, int c) {
    return a < b ?  
                    a<c ? a : c 
                  : b<c ? b : c;
}

int ugly_number_the(int n) {
    vector<int> ugly_number; ugly_number.reserve(n);
    ugly_number.push_back(1);

    int T2, T3, T5;
    T2=T3=T5=0;
    while (static_cast<int>(ugly_number.size()) < n) 
    {
        ugly_number.push_back(min(ugly_number[T2]*2, 
                                  ugly_number[T3]*3, 
                                  ugly_number[T5]*5));

        while(ugly_number[T2]*2 <= ugly_number.back()) ++T2;
        while(ugly_number[T3]*3 <= ugly_number.back()) ++T3;
        while(ugly_number[T5]*5 <= ugly_number.back()) ++T5;
    }

    return ugly_number.back();
}

int main()
{
    int a, b, c;
    while (true) {
        cin >> a >> b >> c;
        cout << min(a, b, c) << endl;
    }
    return 0;
}
