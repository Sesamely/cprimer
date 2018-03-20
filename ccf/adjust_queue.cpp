/************************************************************************
****	> File Name:    	adjust_queue.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月16日 星期五 15时31分13秒
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int find_loc(const vector<int> &queue,int student_id)
{
    int i;
    for (i=0; i<(int)queue.size(); ++i) {
        if (queue[i] == student_id)
            break;
    }
    return i;
}

void move(vector<int> &queue, int student_id, int distance)
{
    int loc = find_loc(queue, student_id);
    if (distance < 0) {
        while (loc-1>=0 && distance!=0) {
            swap(queue[loc], queue[loc-1]);
            ++distance;
            --loc;
        }
    }
    else {
        while (loc+1<(int)queue.size() && distance != 0) {
            swap(queue[loc], queue[loc+1]);
            --distance;
            ++loc;
        }
    }
}

int main()
{
    int n, m;
    vector<int> queue;
    cin >> n >> m;
    for (int i=1; i<=n; ++i)
        queue.push_back(i);
    for (int i=0; i<m; ++i) {
        int student_id, distance;
        cin >> student_id >> distance;
        move(queue, student_id, distance);
    }

    for (int i=0; i<n; ++i) {
        cout << queue[i] << " ";
    }
    cout << endl;

    return 0;
}
