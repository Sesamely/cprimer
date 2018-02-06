/************************************************************************
****	> File Name:    	check_stack_seq.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Tue 06 Feb 2018 03:20:42 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool check(vector<int> v1, vector<int> v2) {
    if (v1.size() != v2.size()) return false;

    stack<int> st;
    int j = 0, i = 0, v1_last = v1.size()-1,
        v2_last = v2.size()-1;
    while (j<=v2_last && i<=v1_last+1) {
        if(st.empty()) {
            if (i!=v1_last+1) {
                st.push(v1[i]);
                cout << "push " << st.top() << endl;
            }
            ++i;
        }
        if (st.top() == v2[j]) {
            cout << "\tpop " << st.top() << endl;
            st.pop();
            ++j;
        }
        else {
            if(i != v1_last+1) {
                st.push(v1[i]);
                cout << "push " << st.top() << endl;
            }
            ++i;
        }
    }

    if (st.empty() && j==v2_last+1) return true;
    cout << "!CANNOT pop " << v2[j] << " TOP of stack is " << st.top() << endl;
    return false;
}

int main()
{
    vector<int> v, v1;
    int i;
    while (cin >> i) {
        if (!i) break;
        v.push_back(i);
    }
    while (cin >> i) v1.push_back(i);
    cout << "result is : " << boolalpha << check(v, v1) << endl;
    return 0;
}
