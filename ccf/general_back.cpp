/************************************************************************
****	> File Name:    	general_back.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月14日 星期三 09时56分57秒
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//不可重复的填充
void general_back_aux(int k, int sum, int target,
                      vector<int> &v,
                      const vector<int> &demo)
{
    if (k == (int)v.size()) return;

    for (int i=0; i<2; ++i) {
        v[k] = i;
        sum += v[k]*demo[k];
        if (sum == target) {
            //target
            for (int i=0; i<(int)v.size(); ++i) {
                if (v[i] != 0)
                    cout << demo[i] << " ";
            }
            cout << endl;

        } else if (sum < target) {
            general_back_aux(k+1, sum, target, v, demo);
        }
    }
    v[k] = 0;
}

void general_back(const vector<int> &demo, int target)
{
    vector<int> v;
    v.assign(demo.size(), 0);
    general_back_aux(0,0,target,v,demo);
}

//可以重复的填充
void general_back_aux2(int stack_sum,int target_sum,
                       stack<int> &st, 
                       const vector<int> &demo)
{
    if (stack_sum > target_sum) return;
    if (stack_sum == target_sum) {
        //find
        vector<int> temp_v;
        while (!st.empty()) {
            temp_v.push_back(st.top());
            st.pop();
        }
        for (const auto &a:temp_v) cout << a << " "; cout << endl;
        for (auto i=temp_v.end()-1; i>=temp_v.begin(); --i) {
            st.push(*i);
        }
    }
    for (int i=0; i<=(int)demo.size(); ++i) {
        st.push(demo[i]);
        general_back_aux2(stack_sum+demo[i], target_sum, st, demo);
        st.pop();
    }
}
void general_back2(const vector<int> &demo, int target)
{
    stack<int> st;
    general_back_aux2(0, target, st, demo);
}

int main()
{
    vector<int> demo = {10, 20, 30, 40, 50, 60};
    int target = 70;
    general_back2(demo, target);
}
