/************************************************************************
****	> File Name:    	subway_build.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月16日 星期五 15时59分53秒
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;


int day = ~(1<<31);

struct edge {
    int src;
    int des;
    int length;
};

struct vertex {
    char has_been_selected;
    vector<edge> edges;
};

void disp(stack<pair<int, int> > &st) {
    if (st.empty()) return;
    pair<int, int> temp_pair;
    int temp = st.top().first;
    temp_pair.first = temp;
    temp_pair.second = st.top().second;
    st.pop();
    disp(st);
    st.push(temp_pair);
    cout << temp << " ";
}

int stack_pair_max(stack<pair<int, int> > &st)
{
    if (st.empty()) return 1<<31;

    pair<int, int> temp_pair;
    temp_pair.first = st.top().first;
    temp_pair.second = st.top().second;

    st.pop();
    int result = stack_pair_max(st);
    st.push(temp_pair);

    return temp_pair.second > result ? temp_pair.second : result;
}

void DFS(vector<vertex> &v, int v_loc, stack<pair<int, int> > &st, int length, int number)
{
    if (v[v_loc].has_been_selected) return;

    pair<int, int> temp_pair;
    temp_pair.first = v_loc;
    temp_pair.second = length;
    st.push(temp_pair);
    v[v_loc].has_been_selected = 1;

    if (number == (int)v.size()-1) {
        if (length < day) day = length;
        return;
    }

    vector<edge> &cur_edges = v[v_loc].edges;
    for (int i=0; i<(int)cur_edges.size(); ++i) {
        int len = cur_edges[i].length > length ? cur_edges[i].length : length;
        DFS(v, cur_edges[i].des, st, len, number+1);
    }

    st.pop();
    v[v_loc].has_been_selected = 0;
}

void init(int n, int m, vector<vertex> &v)
{
    cin >> n >> m;

    int temp1, temp2 ,temp3;
    vertex temp_v;
    temp_v.has_been_selected = 0;
    v.assign(n, temp_v);
    edge temp_e;
    for (int i=0; i<m; ++i) {
        cin >> temp1 >> temp2 >> temp3;
        --temp1;
        --temp2;
        temp_e.src = temp1;
        temp_e.des = temp2;
        temp_e.length = temp3;
        v[temp1].edges.push_back(temp_e);
    }
}

int main()
{
    int n=0, m=0;
    vector<vertex> v;
    stack<pair<int, int> > st;
    init(n, m, v);
    DFS(v, 0, st, 0, 0);

    cout << day << endl;
    return 0;
}
