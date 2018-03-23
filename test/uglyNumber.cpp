/************************************************************************
****	> File Name:    	ugly_numebr.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月12日 星期一 16时17分57秒
************************************************************************/

#include <iostream>
#include <array>
using namespace std;

long min(long a, long b, long c) {
    return a <= b ?
                a <= c ? a : c
            :   b <= c ? b : c;
}

void getUglyNumber(int index)
{
    if (index <= 0) return;

    long array[index];
    unsigned loc2 = 0;
    unsigned loc3 = 0;
    unsigned loc5 = 0;

    array[0] = 1;
    int n=1;
    while (n < index) {
        int uglyNumber = min(array[loc2]*2,
                             array[loc3]*3, array[loc5]*5);
        array[n++] = uglyNumber;
        //cout << uglyNumber << " ";

        while (array[loc2]*2 <= uglyNumber)
            ++loc2;
        while (array[loc3]*3 <= uglyNumber)
            ++loc3;
        while (array[loc5]*5 <= uglyNumber)
            ++loc5;
    }

    long uglyNumberOfIndex = array[index-1];
    cout << uglyNumberOfIndex << endl;

}

int main()
{
    int n;
    cin >> n;
    getUglyNumber(n);

    return 0;
}
