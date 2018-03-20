/************************************************************************
****	> File Name:    	queue.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月13日 星期二 11时01分18秒
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int cnt = 0;

void queue(int index)
{
    if (index <= 0) return;

    vector<int> c;
    c.assign(index, 0);

    int k = 0;

    while (k>=0) {
        int go_back = true;
        while (c[k] <= index-1) {

            int flag = true;
            for (int i=0; i<k&&flag==true; ++i) {
                if (c[i] == c[k]) flag = false;
                if (i-k == c[i]-c[k]) flag = false;
                if (k-i == c[i]-c[k]) flag = false;
            }
            
            if (flag) {
                go_back = false;
                if (k == index-1)
                {
                    ++cnt;
                    for (const auto &a : c) cout << a << " "; 
                    cout << endl;
                    ++c[k];
                    break;
                }//找到了路径
                ++k;
                break;
            }
            else {
                ++c[k];
            }
        }

        if (go_back) {
            c[k] = 0;
            --k;
            if(k>=0) ++c[k];
        }

    }
}


void queue_r(int k, vector<int> &c) {
    for (c[k]=0; c[k]<(int)c.size(); ++c[k]) {
        int flag = true;
        for (int i=0; i<k&&flag==true; ++i) {
            if (c[i] == c[k]) flag = false;
            if (i-k == c[i]-c[k]) flag = false;
            if (k-i == c[i]-c[k]) flag = false;
        }
        if (flag) {
            if (k == (int)c.size()-1) {
                ++cnt;
            }
            else {
                queue_r(k+1, c);
            }
        }
    }
    c[k] = 0;
}


int main1(int argc, char** argv)
{
    if (argc!=2) {
        cout << "useage: elf number" << endl;
        return 0;
    }
    int i = stoi(argv[1]);
    queue(i);

    cout << "number is " << cnt << endl;
    return 0;
}

int main() {
    vector<int> c;
    int index = 4;
    c.assign(index, 0);

    queue_r(0, c);
    cout << cnt << endl;

    return 0;
}
