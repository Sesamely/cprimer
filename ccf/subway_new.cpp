/************************************************************************
****	> File Name:    	subway_new.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月17日 星期六 12时20分40秒
************************************************************************/

#include<iostream>
#include <vector>
#include <stack>
using namespace std;

struct edge {
    int src;
    int des;
    int length;
};

struct vertex {
    int has_been_selected;
    vector<edge> edges;
};

inline void init(int &n, int &m, vector<vertex> &v)
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

int day = ~(1<<31);
int v_size;
void DFS(vector<vertex> &v, int max_length, int v_loc)
{
    //cout << "loc " << v_loc << " push" << endl;
    if (v_loc == v_size-1) {
        if (max_length < day) day = max_length;
        //cout << "loc " << v_loc << " pop" << endl;
        return;
    }
    if (v[v_loc].has_been_selected) return;
    v[v_loc].has_been_selected = 1;

    vector<edge> cur_edges = v[v_loc].edges;
    int cur_edges_number = cur_edges.size();
    for (int i=0; i<cur_edges_number; ++i) {
        int cur_edge_length = cur_edges[i].length;
        int cur_max = max_length;
        if (cur_edge_length > cur_max)
            cur_max = cur_edge_length;
        DFS(v, cur_max, cur_edges[i].des);
    }
    v[v_loc].has_been_selected = 0;
    //cout << "loc " << v_loc << " pop" << endl;
}

int main()
{
    int n, m;
    vector<vertex> v;
    init(n, m, v);
    v_size = n;

    DFS(v, 0, 0);

    cout << day << endl;

    return 0;
}
