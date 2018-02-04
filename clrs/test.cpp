/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 09:46:31 PM CST
************************************************************************/


#include <iostream>
#include <ctime>
#include <typeinfo>
using namespace std;

int main()
{
    time_t timer;
    time(&timer);
    cout << typeid(timer).name() << " " << timer << endl;
    cout << asctime(localtime(&timer)) << endl;
    return 0;
}
