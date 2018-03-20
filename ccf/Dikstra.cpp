/************************************************************************
****	> File Name:    	Dikstra.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月12日 星期一 21时32分13秒
************************************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;
struct vertex;

struct edge {
    static const int MAX_DISTANCE = ~(1<<31);
    int length;
    vertex *des_v;  
};

struct vertex {
    int has_been_selected = 0;
    int front_v = -1;
    int min_distance = edge::MAX_DISTANCE;
    list<edge> edges;
};

void init(vector<vertex> &vertexs) {
    string temp;
    int N, COL;
    cin >> temp >> N >> temp >> COL;
    
    vertex temp_v;
    edge temp_e;
    vertexs.assign(N, temp_v);

    int v_src, v_des, distance;
    for (int i=0; i<COL; ++i) {
        cin >> v_src >> v_des >> distance;
        temp_e.des_v = &vertexs[v_des];
        temp_e.length = distance;
        vertexs[v_src].edges.push_back(temp_e);
    }
}

void dikstra(vector<vertex> &vertexs, int v_src) {

    stack<int> st;
    st.push(v_src);
    vertexs[v_src].min_distance = 0;

    while (!st.empty()) {
        int cur_v_src = st.top();

        st.pop();
        vertexs[cur_v_src].has_been_selected = 1;
        for (const auto &e : vertexs[cur_v_src].edges) {
            if (e.length + vertexs[cur_v_src].min_distance 
                < (e.des_v)->min_distance || 
                (e.des_v)->min_distance == edge::MAX_DISTANCE ) 
            {
                (e.des_v)->front_v = cur_v_src;
                (e.des_v)->min_distance 
                    = e.length + vertexs[cur_v_src].min_distance;
            }
        }
        
        int cur_min_dis = edge::MAX_DISTANCE;
        int cur_min_v = -1;
        int cur_loc = 0;
        for (const auto &v : vertexs) {
            if (!v.has_been_selected) {
                if (v.min_distance < cur_min_dis) {
                    cur_min_dis = v.min_distance;
                    cur_min_v = cur_loc;
                } 
            }
            ++cur_loc;
        }

        if (cur_min_v != -1) {
            st.push(cur_min_v);
        }
    }
}

void disp_path_aux(const vector<vertex> &vertexs, int v_des)
{
    if (v_des== -1)  return ;
    disp_path_aux(vertexs, vertexs[v_des].front_v);
    cout << v_des << " -> ";
}

void disp_adj(const vector<vertex> &);
void disp_path(int src, int des) {
    vector<vertex> vertexs;
    init(vertexs);

    dikstra(vertexs, src);

    if (vertexs[des].min_distance == edge::MAX_DISTANCE) {
        cout << " NO PATH!" << endl;
        return;
    }
    cout << "from " << src << " to " << des << " minimum length is " 
        << vertexs[des].min_distance << "\n\tpath is ";
    disp_path_aux(vertexs, des);
    cout << endl;
    
}

void disp_adj(const vector<vertex> &vertexs) {
    int cur_loc = 0;
    for (const auto & v : vertexs) {
        cout << "v is " << cur_loc << " could to ";
        for (const auto & e : v.edges) {
            cout << e.des_v - &vertexs[0] << 
                " with length " << e.length 
                << ", ";
        }
        cout << endl;

        ++cur_loc;
    }
}

int main()
{
    int src=0,
        des;
    cin >> des;

    disp_path(src, des);

    return 0;
}
