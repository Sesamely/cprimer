/************************************************************************
****	> File Name:    	fibonacci.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 07 Feb 2018 10:33:57 PM CST
************************************************************************/

#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

long long gen_fib(unsigned n) {
    assert(n>=0);
    if (n<2) return n;
    if (n>92) {
        cerr << "CANNOT represent by long long" << endl;
        return -1;
    }

    long long fn_1 = 1,fn_2 = 0, fn_result;
    unsigned num = 2;

    for (; num<=n; ++num) {
        fn_result = fn_1 + fn_2;
        fn_2 = fn_1;
        fn_1 = fn_result;
    }

    return fn_result;
}

int main() {
    unsigned i;
    
    while (cin >> i) {
        cout << setw(4) << i << ":" << setw(20) <<  gen_fib(i) << endl;
    }

    return 0;
}
