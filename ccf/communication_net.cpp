/************************************************************************
****	> File Name:    	communication_net.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月16日 星期五 13时45分53秒
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct net_vertex {
    char has_been_selected;
    vector<int> net_vertexs;
};

inline void init(vector<net_vertex> &v_demo, vector<net_vertex> &v_reverse)
{
    int N, M;
    cin >> N >> M;

    net_vertex temp_vertex;
    temp_vertex.has_been_selected = 0;
    v_demo.assign(N, temp_vertex);
    v_reverse.assign(N, temp_vertex);

    for (int i=0; i<M; ++i) {
        int src, des;
        cin >> src >> des;
        --src; --des;
        v_demo[src].net_vertexs.push_back(des);
        v_reverse[des].net_vertexs.push_back(src);
    }
}

inline bool BFP_judge(vector<net_vertex> &v, int src)
{
    for (int i=0; i<(int)v.size(); ++i) {
        v[i].has_been_selected = 0;
    }

    stack<int> st;
    st.push(src);

    while (!st.empty()) {
        int cur_v = st.top();
        v[cur_v].has_been_selected = 1;
        st.pop();

        vector<int> &net_vertexs = v[cur_v].net_vertexs;
        for (int i=0; i<(int)net_vertexs.size(); ++i) {
            if (!v[net_vertexs[i]].has_been_selected) {
                st.push(net_vertexs[i]);
            }
        }
    }

    for (int i=0; i<(int)v.size(); ++i) {
        if (!v[i].has_been_selected) {
            bool flag = false;
            vector<int> &net_vertexs = v[i].net_vertexs;
            for (int j=0; j<(int)net_vertexs.size(); ++j) {
                if (net_vertexs[j] == src) flag = true;
            }
            if (!flag) return false;
        }
    }

    return true;
}

int main()
{
    vector<net_vertex> v1, v2;
    vector<int > judge_v;
    init(v1, v2);
    judge_v.assign(v1.size(), 0);
    int cnt = 0;
/*
 *    for (int i=0; i<(int)v1.size(); ++i) {
 *        for (int i=0; i<(int)judge_v.size(); ++i)
 *            judge_v[i] = 0;
 *        BFP_judge(v1, i);
 *        for (int i=0; i<(int)v1.size(); ++i) {
 *            if (v1[i].has_been_selected)
 *                judge_v[i] = 1;
 *        }
 *        BFP_judge(v2, i);
 *        for (int i=0; i<(int)v2.size(); ++i) {
 *            if (v2[i].has_been_selected)
 *                judge_v[i] = 1;
 *        }
 *
 *        for (int i=0; i<(int)judge_v.size(); ++i) {
 *            if (!judge_v[i]) continue;
 *        }
 *        ++cnt;
 *    }
 */
    for (int i=0; i<(int)v1.size(); ++i) {
        if (BFP_judge(v1, i) || BFP_judge(v2, i))
            ++cnt;
    }
    cout << cnt << endl;
    return 0;
}
