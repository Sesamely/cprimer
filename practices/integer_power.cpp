/************************************************************************
****	> File Name:    	integer_power.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 05 Feb 2018 03:55:39 PM CST
************************************************************************/

#include <iostream>
#include <bitset>
using namespace std;

double unsigned_power(double, unsigned);
double power(double base, int exponent)
{
    if (base == 0) {
        if (exponent<=0) return -1;
        else return 0.0;
    }
    unsigned unsigned_exponent = exponent > 0 ? 
                                    exponent : (~exponent + 1);
    double result = unsigned_power(base, unsigned_exponent);
    if (exponent < 0) result = 1 / result;

    return result;
}
double unsigned_power(double base, unsigned exponent)
{
    if (exponent == 0) return 1;
    if (exponent == 1) return base;

    double result = unsigned_power(base, exponent>>1);
    result *= result;
    if (exponent & 0x1) {
        result *= base;
    }

    return result;
}

int main()
{
    double base;
    int exponent;
    cout << "base is: "; cin >> base;
    cout << "exponent is: "; cin >> exponent;
    cout << base << "^(" << exponent << ") is: " <<
        power(base, exponent) << endl;

    return 0;
}
