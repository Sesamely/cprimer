/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月17日 星期六 11时43分25秒
************************************************************************/

#include<iostream>
#include<stack>
using namespace std;

int main()
{
    stack<pair<int, int> > st;
    st.push({1, 2});

    cout << st.top().first << st.top().second << endl;

    return 0;
}
