/************************************************************************
****	> File Name:    	before_tax.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月17日 星期六 15时31分12秒
************************************************************************/

#include<iostream>
#include <vector>
using namespace std;


int main()
{
    /*
     *int range[] = {1500, 3000, 4500, 26000, 20000, 25000, 0};
     *int floor[] = {0, 1500, 4500, 9000, 35000, 55000, 80000};
     */
    double sui_lv[] = {0.03, 0.1, 0.2, 0.25, 0.30, 0.35, 0.45};
    int jiao_le_de_qian[] = {45, 300, 900, 6500, 6000, 8750, 0};
    int shiji_fanwei[] = {1455, 4155, 7755, 27255, 41255, 57505};
    int T;
    cin >> T;
    int S=T;
    T = T - 3500;
    int fanwei = 6;
    int i;
    for (i=0; i<fanwei&&shiji_fanwei[i]<=T; ++i) {
        S += jiao_le_de_qian[i];
    }
    cout << " i is " << i  << endl;
    if (i==0) {
        cout << S << endl;
        return 0;
    }
    int dis = T - shiji_fanwei[i-1];
    cout << "dis is " << dis << endl;
    S += dis / (1 - sui_lv[i]) * sui_lv[i];

    cout << S << endl;

    return 0;
}

