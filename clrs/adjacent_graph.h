/************************************************************************
****	> File Name:    	adjacent_graph.h
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 05:00:43 PM CST
************************************************************************/

#ifndef _ADJACENT_GRAPH_H
#define _ADJACENT_GRAPH_H

#include <iomanip>
#include <forward_list>
#include <vector>
#include <iostream>
#include <map>
using namespace std;


enum color {
    WHITE, GRAY, BLACK
};
struct vertex {
    const int key;
    color c;
    int d;
    int f;
    vertex *pre_v;

    vertex() = default;
    vertex(int k, color color) : key(k), c(color), d(0), f(0),
                                pre_v(nullptr) {}

    bool operator<(const vertex other_v) const {
        return this->key < other_v.key;
    }
};
struct adjacent_list {
    vector<vertex> vs;
    map<vertex, forward_list<vertex *>> adj;
    
    forward_list<vertex *> &operator[](const vertex &i) {
        return adj[i];
    }

    void add_vertex(int key, color col) {
        vs.emplace_back(key,col);
    }

    vertex *find_key_of(int key) {
        for (auto &i : vs) {
            if (i.key == key) return &i;
        }
        return nullptr;
    }

    bool add_edge(const int key_1, const int key_2) {
        auto v1 = find_key_of(key_1);
        auto v2 = find_key_of(key_2);
        if (v1==nullptr || v2==nullptr) return false;
        adj[*v1].push_front(v2);
        return true;
    }
};

/*Global variables*/
int cur_time;
forward_list<vertex *> list_for_topologic;

void disp_adj(adjacent_list &adj)
{
    for (const auto &i : adj.vs) {
        cout << "v.key is: " << i.key
            << " —— list key_value is: ";
        for (const auto &j : adj[i]) {
            if (j) cout << j->key << " ";
            else cout << "  ";
        }
        cout << endl;
    }
}
void get_adjacent_list(istream &in, adjacent_list &adj) {
    string temp_str;
    int temp_int, temp_int1;
    char temp_char;

    in >> temp_str;
    if (temp_str != "V:" || !in.good()) {
        in.setstate(iostream::failbit);
        cerr << "fail, NO 'V:' !" << endl;
    }
    while (in >> temp_int) {
        adj.add_vertex(temp_int, WHITE);
    }
    in.clear();

    in >> temp_str;
    if (!in.good() || temp_str != "E:") {
        in.setstate(iostream::failbit);
        cerr << "fail, NO 'E:' !" << endl;
    }

    while (in >> temp_char) {
        if (!in.good() || temp_char != '(') {
            in.setstate(iostream::failbit);
            cerr << "file NO '(' !" << endl; break;
        }
        in >> temp_int;
        if (!in.good()) {cerr << "NOT number !!" << endl;break;}
        in >> temp_char;
        if (!in.good() || temp_char != ',') {
            in.setstate(iostream::failbit);
            cerr << "file NO ',' !" << endl; break;
        }
        in >> temp_int1;
        if (!in.good()) {cerr << "NOT number !!" << endl;break;}
        adj.add_edge(temp_int, temp_int1);

        in >> temp_char;
        if (!in.good() || temp_char != ')') {
            in.setstate(iostream::failbit);
            cerr << "file NO ')' !" << endl; break;
        }
    }
}
#endif
