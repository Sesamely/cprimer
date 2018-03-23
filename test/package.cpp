/************************************************************************
****	> File Name:    	package.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月12日 星期一 13时42分15秒
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    vector<int> objects;
    int i, p_v=0, max_v;
    while (cin >> i) {
        objects.push_back(i);
    }
    if (objects.size() == 0) {
        cout << "No objects..." << endl;
        return 0;
    }

    cin >> max_v;


    vector<char> objects_has_been_taken;
    for (i=0; i<(int)objects.size(); ++i) {
        objects_has_been_taken.push_back(0);
    }
    int num = 1, max;
    stack<int> sk, max_sk;
    p_v += objects[0];
    max = p_v;
    sk.push(0);


    int j = 1;
    while (num > 0) {
        while (j < (int)objects.size()) {
            if (!objects_has_been_taken[j]) {
                p_v += objects[j];
                if (p_v > max_v) {
                    p_v -= objects[j];
                }
                else {
                    sk.push(j);
                    objects_has_been_taken[j] = 1;
                    if (p_v > max) {
                        max = p_v;
                        max_sk = sk;
                    }
                }
            }
        }
    }

}
