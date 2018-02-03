/************************************************************************
****	> File Name:    	activity_select.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 01 Feb 2018 03:23:07 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void activity_select_dp(const vector<int> &s,
                       const vector<int> &f,
                       vector<vector<int>> &c,
                       vector<vector<int>> &sel)
{
    const int first_act = 1,
                last_act = s.size()-1,
                max_step = last_act - first_act + 1;
    int step,
        i, j, k;
    c.reserve(s.size()); sel.reserve(f.size());
    for (i=0; i<=last_act; ++i) {
        sel[i].reserve(s.size());
        c[i].reserve(s.size());
        c[i][i] = 0;
    }

    for (step=3; step<=max_step; ++step) {
        for (i=first_act; i<=last_act-step+1; ++i) {
            j = i + step -1;
            for (k=i; k<j; ++k) {}
        }
    }

}

int activity_select_dp_recursive_auxiliary(const vector<int> &s,
                                const vector<int> &f,
                                int i, int j, const int n,
                                vector<vector<int>> &c,
                                vector<vector<int>> &sel)
{
    if (c[i][j] >= 0) return c[i][j];

    int k, max = 0;
    for (k=1; k<=n; ++k) {
        if (k==i || k==j) continue;
        int temp;
        if (s[k]>=f[i] && f[k]<=s[j]) {
            temp = activity_select_dp_recursive_auxiliary(s, f, i, k, n, c, sel)
                + activity_select_dp_recursive_auxiliary(s, f, k, j, n, c, sel) + 1;
            if (temp > max) {
                max = temp;
                sel[i][j] = k;
            }
        }
    }
    c[i][j] = max;
    return c[i][j];
}

void disp_sel_auxiliary(const vector<vector<int>> &sel, int i, int j) {
    if (sel[i][j] == -1) return;
    int act_num = sel[i][j];
    disp_sel_auxiliary(sel, i, act_num);
    cout << setw(4) << left << act_num; 
    disp_sel_auxiliary(sel, act_num, j);
}

int activity_select_dp_recursive(const vector<int> &s,
                                const vector<int> &f,
                                const int before_start,
                                const int after_end)
{
    int i, j,
        result = 0,
        size = s.size();
    vector<vector<int>> c, sel;
    c.reserve(s.size()); sel.reserve(f.size());
    for (i=0; i<size; ++i) {
        c[i].reserve(s.size());
        sel[i].reserve(s.size());
        for (j=0; j<size; ++j) {
            c[i][j]  = -1;
            sel[i][j] = -1;
        }
    }

    result = activity_select_dp_recursive_auxiliary(s, f, before_start,
                                                    after_end,
                                                    size-1, c, sel);
    
    cout << "number: \t";
    for (i=1; i<size-1; ++i) cout << setw(5) << i; cout << "\n";
    cout << "start_time: \t";
    for (i=1; i<size-1; ++i) cout << setw(5) << s[i]; cout << "\n";
    cout << "finish_time: \t";
    for (i=1; i<size-1; ++i) cout << setw(5) << f[i]; cout << "\n";
    cout << "the number selected: ";
    disp_sel_auxiliary(sel, before_start, after_end);
    cout << endl;
    
    /*
     *cout << "\n   ";
     *for (i=0; i<size; ++i) cout << setw(2) << i << " ";
     *cout << endl;
     *for (i=0; i<size; ++i) {
     *    cout << setw(2) << i << " ";
     *    for (j=0; j<size; ++j) {
     *        if (c[i][j] == -1) cout << " - ";
     *        else cout << setw(2) << c[i][j] << " ";
     *    }
     *    cout << endl;
     *}
     *cout << endl;
     */

    /*
     *for (i=0; i<size; ++i) {
     *    for (j=0; j<size; ++j) {
     *        if (sel[i][j] == -1) cout << "   ";
     *        else cout << setw(2) << sel[i][j] << " ";
     *    }
     *    cout << endl;
     *}
     *cout << endl;
     */

    return result;
}
/*以下为贪心的递归版本*/
void activity_select_greedy_recursive(const vector<int> &s,
                                     const vector<int> &f,
                                     int k, const int n,
                                     vector<int> &selected_act)
{
    int m = k + 1;
    while (m<=n && s[m] < f[k]) ++m;
    if (m <= n) {
        selected_act.push_back(m);
        activity_select_greedy_recursive(s, f, m, n,
                                                selected_act);
    }
}

/**************************************************************/
int main()
{
    int i, result;
    vector<int> s, f;

    s.push_back(0);
    f.push_back(0);

    while (cin >> i) {
        if (!i) break;
        s.push_back(i);
    }
    while (cin >> i) f.push_back(i);

    s.push_back(~(1<<31)); f.push_back(~(1<<31));
    
    result = activity_select_dp_recursive(s, f, 0, s.size()-1);
    
    cout << "activity_set max length is: " << result << endl;

    return 0;
}
int main1()
{
    int i;
    vector<int> s, f, selected_act_seq;

    s.push_back(0);
    f.push_back(0);

    while (cin >> i) {
        if (!i) break;
        s.push_back(i);
    }
    while (cin >> i) f.push_back(i);

    activity_select_greedy_recursive(s, f, 0, s.size()-1, selected_act_seq);
    
    for (const auto &i : selected_act_seq) cout << i << " ";
    cout << "\tsumsize is: " << selected_act_seq.size() << endl;

    return 0;
}
