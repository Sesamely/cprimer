/************************************************************************
****	> File Name:    	graph_s.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 10:06:07 PM CST
************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <queue>

#include "./adjacent_graph.h"
using namespace std;

void bfs(adjacent_list &adj, vertex &v)
{
    queue<vertex *> vertex_queue((deque<vertex *>()));

    v.d = 0;
    v.c = GRAY;
    vertex_queue.push(&v);
    while (!vertex_queue.empty()) {
        vertex *u = vertex_queue.front();
        vertex_queue.pop();
        for (auto &i : adj[*u]) {
            if (i->c == WHITE) {
                i->d = u->d + 1;
                i->c = GRAY;
                i->pre_v = u;
                vertex_queue.push(i);
            }
        }
        //u->c = BLACK;
    }
}

void print_from_s_to_v(const adjacent_list &adj,
                       const vertex &s, const vertex &v)
{
    if (v.key == s.key) cout << v.key << "->";
    
    else if (v.pre_v == nullptr) {
        cout << "NO path from s to v !" << endl;
    }
    else {
        print_from_s_to_v(adj, s, *v.pre_v);    
        cout << v.key << "->";
    }
}

int main()
{
    adjacent_list adj;
    ifstream fin("./text_for_graph");
    get_adjacent_list(fin, adj);

    auto s = adj.find_key_of(1),
        v = adj.find_key_of(3);
    bfs(adj, *s);

    print_from_s_to_v(adj, *s, *v);
    cout << endl;
    
    return 0;
}
