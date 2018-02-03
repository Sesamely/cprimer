/************************************************************************
****	> File Name:    	cut_rod.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 27 Jan 2018 09:22:56 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;
#define MAX_SIZE_R 100
#define FIXED_COST 2

int cut_rod(vector<int> p, int n)
{
    if (n==0) return 0;
    int q=-1;
    for (int i=0; i++!=n; ) {
        int temp = p[i] + cut_rod(p, n-i);
        q = q > temp ? q : temp;
    }
    return q;
}

int memorized_cut_rod_auxiliary(const vector<int> &p, int n,
                                vector<int> &r,
                                vector<int> &s)
{
    if (n == 0) return 0;
    if (r[n] > 0) return r[n];

    int q = 1<<31, i;
    for (i=1; i<=n ; ++i) {
        int temp = p[i] + memorized_cut_rod_auxiliary(p, n-i, r, s);
        if (q < temp) {
            q = temp;
            s[n] = i;
        }
    }
    r[n] = q;
    return q;
}

int memorized_cut_rod(const vector<int> &p, int n)
{
    vector<int> r; r.reserve(MAX_SIZE_R);
    vector<int> s; s.reserve(MAX_SIZE_R);
    for(int i=0; i<=MAX_SIZE_R; ++i) r.push_back(1<<31);
    int result = memorized_cut_rod_auxiliary(p, n, r, s);
    
    int current_len = n;
    cout << "schema is: ";
    while(current_len > 0) {
        cout << s[current_len] << ' ';
        current_len -= s[current_len];
    }
    cout << "\tresult is :";
    return result;
}

int bottom_up_cut_rod(const vector<int> &p, unsigned n)
{
    vector<int> r; r.reserve(p.size()*10);
    vector<int> s; s.reserve(p.size()*10);
    unsigned i, j;
    for (i=0; i<p.size(); ++i) r.push_back(1<<31);
    r[0] = 0;

    for (i = 1; i <= n; ++i) {
        int price = 1<<31;
        for (j = 1; j<=i; ++j) {
            int temp = p[j] + r[i-j];
            if (i-j) temp -= FIXED_COST;
            if (price < temp) {
                price = temp;
                s[i] = j;
            } 
        }
        r[i] = price;
    }
    int current_len = n;
    cout << "schema is: ";
    while(current_len > 0) {
        cout << s[current_len] << ' ';
        current_len -= s[current_len];
    }
    cout << "\tresult is :";
    return r[n];
}

int main()
{
    vector<int> p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n;
    cin >> n;
    cout << bottom_up_cut_rod(p, n) << endl;

    return 0;
}
