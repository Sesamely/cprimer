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

void dfs_auxiliary(adjacent_list &adj, vertex &v)
{
    cout << v.key << "->";
    ++cur_time;
    v.d = cur_time;
    v.c = GRAY;
    for (auto &u : adj[v]) {
        if (u->c == WHITE) {
            u->pre_v = &v;
            dfs_auxiliary(adj, *u);
        }
    }
    ++cur_time;
    v.f = cur_time;
    v.c = BLACK;
    list_for_topologic.push_front(&v);
}
void dfs(adjacent_list &adj)
{
    cur_time = 0;
    
    for (auto &u : adj.vs) {
        if (u.c == WHITE) {
            dfs_auxiliary(adj, u);
            cout << endl;
        }
    }
}
void print_dfs_time(const adjacent_list &adj)
{
    for (const auto &i : adj.vs) {
        cout << "key is: " << i.key << " \tfind time is: " << setw(4)
            << left << i.d << " finish time is: " << setw(4) << i.f << endl;
    }
}
//use v.d represent the in-degree;
void topologic_sort_bfs(adjacent_list &adj)
{
    vector<vertex *> vertex_vector_for_list;
    queue<vertex *> vertex_queue((deque<vertex *>()));
    for (auto &v : adj.vs) {
        v.d = 0;
    }
    for (auto &v : adj.vs) {
        for (auto u : adj[v]) {
            ++u->d;
        }
    }
    for (auto &v : adj.vs) {
        if (v.d == 0) vertex_queue.push(&v);
    }
    while (!vertex_queue.empty()) {
        vertex *temp_v = vertex_queue.front();
        vertex_vector_for_list.push_back(std::move(temp_v));
        vertex_queue.pop();
        for (auto u : adj[*temp_v]) {
            if (u->d > 0) --u->d;
            if (u->d == 0) vertex_queue.push(u);
        }
    }
    list_for_topologic.assign(vertex_vector_for_list.cbegin(),
                                vertex_vector_for_list.cend());
}
int main()
{
    adjacent_list adj;
    get_adjacent_list(cin, adj);

    auto s = adj.find_key_of(6),
        v = adj.find_key_of(4);
    
    if (s!=nullptr && v!=nullptr) {
        bfs(adj, *s);
        print_from_s_to_v(adj, *s, *v);
    }
    cout << endl;
    
    return 0;
}


int main1()
{
    adjacent_list adj;
    get_adjacent_list(cin, adj);

    /*
     *dfs(adj);
     *print_dfs_time(adj);
     */

    topologic_sort_bfs(adj);
    for (const auto &i : list_for_topologic) cout << i->key << "->";
    cout << endl;

    return 0;
}
