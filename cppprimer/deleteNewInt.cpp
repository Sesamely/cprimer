/************************************************************************
****	> File Name:    	deleteNewInt.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 12:46:50 AM CST
************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int *i = new int(2018);
    cout << i << ' ';
    cout << *i << endl;
    delete i;
    cout << i << ' ';
    cout << *i << endl;
    return 0;
}
