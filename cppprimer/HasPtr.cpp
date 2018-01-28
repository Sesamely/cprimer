/************************************************************************
****	> File Name:    	HasPtr.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 08:50:23 PM CST
************************************************************************/

#include "./HasPtr.h"

int main()
{
    HasPtr hp("liuyiwen"), hp1, hp2, hp4("string");
    hp1 = hp;
    hp2 = hp1; 
    hp4 = hp2;
    {
        HasPtr hp3 = hp;
        hp3.dispString();
    }
    hp.dispString();
    hp1.dispString();
    hp2.dispString();
    hp4.dispString();
    return 0;
}
