/************************************************************************
****	> File Name:    	crontab_ccf.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Thu 01 Mar 2018 06:46:40 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
using namespace std;

void my_stovi(const string &s, vector<int> &vi) {
    unsigned i=0;
    int temp_i;
    list<int> li;
    string temp_s = "";
    for (; i<s.length(); ++i) {
        if (isdigit(s[i]))    
            temp_s.push_back(s[i]);
        else if (s[i] == ',') {
            temp_i = stoi(temp_s);
            temp_s = "";
            vi.push_back(temp_i);
        }
        else if (s[i] == '-') {
            temp_i = stoi(temp_s);
            temp_s = "";
            ++i;
            while (isdigit(s[i])) {
                temp_s.push_back(s[i]);
                ++i;
            }
            if (i != s.length()) --i;
            int min=temp_i, max;
            max = stoi(temp_s);
            temp_s = "";
            for (; min<=max;  ++min) {
                vi.push_back(min);
            }
        }
    }
    if (temp_s != "") {
        temp_i = stoi(temp_s);
        vi.push_back(temp_i);
    }
}
void 
vvs_format(const vector<vector<string>> &vvs, 
        vector<vector<vector<int>> > &vvv) {
    vector<vector<int>> vv;
    vector<int> vi;
    for (const vector<string> &vs : vvs) {
        for (const string &s : vs) {
            my_stovi(s, vi);
            vv.push_back(vi);
        }
        vvv.push_back(vv);
    }
}

bool match(int cur_time, vector<vector<vector<int>>> &vvv) {
    bool flag1, flag2, flag3, flag4, flag5;
    int yyyy, mm, dd, HH, MM;

    if ()
}

int main()
{
    int n, t, s;
    cin >> n >> t >> s;
    vector<vector<string> > vvs;
    
    int i;
    for (i=0; i<n; ++i) {
        vector<string> vs;
        string s;
        istringstream os;
        getline(cin, s);
        os.str(s);
        while (os >> s) {
            vs.push_back(s);
        }
        vvs.push_back(vs);
    }

    int i=t;
    for (; i<=s; ++i) {
        
    }
}
