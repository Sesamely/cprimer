/************************************************************************
****	> File Name:    	public_key_box.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 01 Mar 2018 08:09:36 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

int find_first_void(vector<int> &key_box) {
    unsigned i=0;
    for (; i<key_box.size(); ++i) {
        if (key_box[i] == 0) return i;
    }
    return -1;
}

void mov_key(int key, vector<int> &key_box) {
    unsigned i = 0;
    for (; i<key_box.size(); ++i) {
        if (key_box[i] == key) {
            key_box[i] = 0;
            return;
        }
    }
}

int main()
{
    vector<vector<int> > vvi;
    vector<int> vi;
    vi.push_back(0);
    for (int i=0; i<20000; ++i) {
        vvi.push_back(vi);
    }

    vector<int> key_box;
    int N,K,w,s,c;
    cin >> N >> K;

    int i;
    key_box.reserve(N);
    for (i=1; i<=N; ++i) {
        key_box.push_back(i);
    }

    int last_time = 0;
    for (i=0; i<K; ++i) {
        cin >> w >> s >> c;
        int e = s+c;
        if (e > last_time) last_time = e;
        vvi[s][0] = w;
        vvi[e].push_back(w);
    }

    for (i=1; i<=last_time; ++i) {
        for (unsigned j=1; j<vvi[i].size(); ++j) {
            int min=vvi[i][j], minloc=j;
            for (unsigned k=j+1; k<vvi[i].size(); ++k) {
                if (min >= vvi[i][k]) {
                    minloc = k;
                    min = vvi[i][k];
                }
            }
            if (minloc != (int)j) swap(vvi[i][minloc],vvi[i][j]);
            int loc = find_first_void(key_box);
            key_box[loc] = vvi[i][j];
        }
        if (vvi[i][0]!=0) {
            mov_key(vvi[i][0], key_box);
        }
    }

    for (i=0; i<(int)key_box.size(); ++i) {
        cout << key_box[i] << " ";
    }
    return 0;
}

