/************************************************************************
****	> File Name:    	partten_match.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sun 04 Feb 2018 11:08:07 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void rabin_karp(string T,
                string P,
                //int d=10, int q=11)
                int d=10, int q=1073741827)
{
    int n = T.size(),
        m = P.size(),
        p = 0,
        t = 0;

    for (int i=0; i<m; ++i) {
        p = ((static_cast<int>(P[i])-48) + p * d) % q;
    }
    for (int i=0; i<m; ++i) {
        t = ((static_cast<int>(T[i])-48) + t * d) % q;
    }

    int h = 1;
    for (int i=1; i<m; ++i) {
        h *= d % q;
    }

    for (int i=0; i<=n-m; ++i) {
        if (t==p) {
            int flag=1;
            for (int j=0; j<m; ++j) {
                if (T[i+j] != P[j]) flag = 0; 
            }
            if (flag) {
                cout << "s is: " << i << " \tSeq is: ";
                for (int j=0; j<m; ++j) {
                    cout << T[i+j] << " ";
                }
                cout << endl;
            }
        }
        t = ( d*(t - (h*(static_cast<int>(T[i])-48)))
                + (static_cast<int>(T[i+m])-48) ) % q;
        if (t<0) t += q;
    }
}

int main()
{
    string P, T;
    char c;
    
    while (cin >> c) {
        if (c=='!') break;
        P.push_back(c);
    }
    while (cin >> c) T.push_back(c);

    rabin_karp(T, P);
    return 0;
}

