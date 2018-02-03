/************************************************************************
****	> File Name:    	reduce.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sun 28 Jan 2018 04:17:48 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;


int cnt;
void merge(vector<int> &v, int p, int q, int r)
{
    vector<int> v1, v2;
    v1.reserve(q-p+2);
    v2.reserve(r-q+1);
    int i,j,k;
    for (i=p; i<=q; ++i) v1.push_back(v[i]);
    for (; i<=r; ++i) v2.push_back(v[i]);
    v1.push_back(static_cast<int>(~(1<<31)));
    v2.push_back(static_cast<int>(~(1<<31)));
    i = j = 0;
    for (k=p; k<=r; ++k) {
        //v[k] = v1[i] <= v2[j] ? v1[i++] : v2[j++];
        if (v1[i] <= v2[j]) {
            v[k] = v1[i++];
        }
        else {
            v[k] = v2[j++];
            cnt += v1.size()-1-i;
        }
    } 
    //for (const auto &i:v) cout << i << ' '; cout << endl; 
}

void reduce(vector<int>& v, int p, int q)
{
    if (p >= q) return ;
    int mid = (p + q) / 2;
    reduce(v, p, mid);
    reduce(v, mid+1, q);
    merge(v, p, mid, q);
}

void reduce2(vector<int> &v, int p, int q, int step=1)
{
    int n = step, i, j, k;
    while(n < q-p+1) {
        for (i=p ; i<=q; i+=n*2) {
            j = i + n - 1;
            k = i + n*2 - 1;
            if (j >= q) break;
            if (k > q) k = q;
            merge(v, i, j, k);
        }
        n = n << 1;
    }    
}
int main()
{
    int i;
    vector<int> v;
    v.reserve(100);
    while(cin >> i) v.push_back(i);
    cnt = 0;
    reduce2(v, 0, v.size()-1);
    /*cout << "inversion pairs: " << cnt << endl;*/
    for (const auto &i : v) cout << i << " "; cout << endl;
    return 0;
}
