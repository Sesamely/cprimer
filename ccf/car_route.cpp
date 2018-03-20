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
    int not_road;
    int length;
    vertex *des_v;  
};

struct vertex {
    int has_been_selected ;
    int front_v ;
    int front_not_road ;
    int min_distance ;
    list<edge> edges;
};

void init(vector<vertex> &vertexs) {
    int N, COL;

    cin >> N >> COL; N += 1;
    
    vertex temp_v;
    temp_v.has_been_selected = 0;
    temp_v.front_v = -1;
    temp_v.front_not_road = 0;
    temp_v.min_distance = edge::MAX_DISTANCE;
    vertexs.assign(N, temp_v);
    vertexs[0].has_been_selected = 1;

    edge temp_e;

    int not_road, v_src, v_des, distance;
    for (int i=0; i<COL; ++i) {
        cin >> not_road >> v_src >> v_des >> distance;
        temp_e.des_v = &vertexs[v_des];
        temp_e.length = distance;
        temp_e.not_road = not_road;
        vertexs[v_src].edges.push_back(temp_e);
    }
}

int add_trace_length(const vector<vertex> &vertexs, int &v) {
    if (!vertexs[v].front_not_road) return 0;
    int front_v = vertexs[v].front_v;
    int length=0;
    for (list<edge>::const_iterator i=vertexs[front_v].edges.begin();
            i!=vertexs[vertexs[v].front_v].edges.end(); ++i)
    {
        if (i->des_v == &vertexs[v])
            length = i->length;
    }
    v=front_v;

    return length + add_trace_length(vertexs, v);
}

void dikstra(vector<vertex> &vertexs, int v_src) {

    stack<int> st;
    st.push(v_src);
    vertexs[v_src].min_distance = 0;

    while (!st.empty()) {
        int cur_v_src = st.top();

        st.pop();
        vertexs[cur_v_src].has_been_selected = 1;
        for(list<edge>::iterator i=vertexs[cur_v_src].edges.begin(); 
                i!=vertexs[cur_v_src].edges.end(); ++i) {
            edge &e = *i;
                    int new_min = edge::MAX_DISTANCE;
                    int temp_v = cur_v_src;
                    if (e.not_road) {

                        new_min =  e.length + add_trace_length(vertexs, temp_v);
                        if (new_min * new_min + vertexs[temp_v].min_distance <
                                (e.des_v)->min_distance)       
                        {
                            (e.des_v)->front_not_road = e.not_road;
                            (e.des_v)->front_v = cur_v_src;
                            (e.des_v)->min_distance 
                            = new_min * new_min + vertexs[temp_v].min_distance;
                        }
                    } else {

                        if (e.length + vertexs[cur_v_src].min_distance
                            < (e.des_v)->min_distance) {
                                (e.des_v)->front_not_road = e.not_road;
                                (e.des_v)->front_v = cur_v_src;
                                (e.des_v)->min_distance =
                                    e.length + vertexs[cur_v_src].min_distance;
                            }
                    }
        }
        
        int cur_min_dis = edge::MAX_DISTANCE;
        int cur_min_v = -1;
        int cur_loc = 0;
        for (int i=0; i<(int)vertexs.size(); ++i) {
            vertex &v = vertexs[i];
            if (!v.has_been_selected) {
                if (v.min_distance < cur_min_dis) {
                    cur_min_dis = v.min_distance;
                    cur_min_v = cur_loc;
                } 
            }
            ++cur_loc;
        }

        if (cur_min_v != -1) {

            if (cur_min_v == (int)vertexs.size()) break;
            st.push(cur_min_v);
        }
    }
}
int main()
{
    vector<vertex> vertexs;
    init(vertexs);
    dikstra(vertexs, 1);
    cout << vertexs[vertexs.size()-1].min_distance ;
    return 0;
}
