/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Fri 02 Mar 2018 04:32:11 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void inc(vector<char> &vc, int i) {
    if (vc[i] != 'D') {
        ++vc[i];
    }
    else {
        vc[i] = 'A';
        inc(vc, ++i);
    }
}
bool match(const vector<char> &vc) {
    //2
    if (vc[1] == 'A' && vc[4] != 'C') return false; 
    if (vc[1] == 'B' && vc[4] != 'D') return false; 
    if (vc[1] == 'C' && vc[4] != 'A') return false; 
    if (vc[1] == 'D' && vc[4] != 'B') return false;
    //3
    switch (vc[2]) {
        case 'A': if (! (vc[2] != vc[5] && vc[5] == vc[1] && vc[5] == vc[3])) return false; break;
        case 'B': if (! (vc[2] != vc[5] && vc[2] == vc[1] && vc[2] == vc[3])) return false; break;
        case 'C': if (! (vc[1] != vc[5] && vc[5] == vc[2] && vc[5] == vc[3])) return false; break;
        case 'D': if (! (vc[3] != vc[1] && vc[5] == vc[1] && vc[5] == vc[2])) return false; break;
    }
    //4
    switch (vc[3]) {
        case 'A': if (vc[0] != vc[4]) return false; break;
        case 'B': if (vc[1] != vc[6]) return false; break;
        case 'C': if (vc[0] != vc[8]) return false; break;
        case 'D': if (vc[5] != vc[9]) return false; break;
    }
    //5
    switch (vc[4]) {
        case 'A': if (vc[7] != 'A') return false; break;
        case 'B': if (vc[3] != 'B') return false; break;
        case 'C': if (vc[8] != 'C') return false; break;
        case 'D': if (vc[6] != 'D') return false; break;
    }
    //6
    switch (vc[5]) {
        case 'A': if (vc[1] != vc[7] || vc[3] != vc[7]) return false; break;
        case 'B': if (vc[0] != vc[7] || vc[5] != vc[7]) return false; break;
        case 'C': if (vc[2] != vc[7] || vc[9] != vc[7]) return false; break;
        case 'D': if (vc[4] != vc[7] || vc[8] != vc[7]) return false; break;
    }
    //7
    int max_cnt[4] = {};
    for (int i=0; i<10; ++i) {
        switch (vc[i]) {
            case 'A': ++max_cnt[0]; break;
            case 'B': ++max_cnt[1]; break;
            case 'C': ++max_cnt[2]; break;
            case 'D': ++max_cnt[3]; break;
        }
    }
    int min_loc=0;
    int min_value = ~(1<<31);
    for (int i=0; i<4; ++i) {
        if (max_cnt[i] < min_value) {
            min_loc = i;
            min_value = max_cnt[i];
        }
    }
    /*
     *cout << endl;
     *cout << "min_loc is " << min_loc << endl;
     *cout << "value is " << max_cnt[min_loc] << endl;
     *for (const auto &a:vc) cout << a << " "; cout << "\n" << endl;
     */
    switch (vc[6]) {
        case 'A': if (min_loc != 2) return false; break;
        case 'B': if (min_loc != 1) return false; break;
        case 'C': if (min_loc != 0) return false; break;
        case 'D': if (min_loc != 3) return false; break;
    }
    //8
    /*
     *cout << "\n\n\n8\n\n\n" ;
     *for (const auto &a:vc) cout << a << " "; cout << "\n" << endl;
     *cout << vc[0] - vc[6] << endl;
     */
    switch (vc[7]) {
        case 'A': if ( (vc[0] - vc[6] <= 1 && vc[0] - vc[6] >= -1)) return false; break;
        case 'B': if ( (vc[0] - vc[4] <= 1 && vc[0] - vc[4] >= -1)) return false; break;
        case 'C': if ( (vc[0] - vc[1] <= 1 && vc[0] - vc[1] >= -1)) return false; break;
        case 'D': if ( (vc[0] - vc[9] <= 1 && vc[0] - vc[9] >= -1)) return false; break;
    }
    //9
    /*
     *cout << "\n\n\n9\n\n\n" ;
     *for (const auto &a:vc) cout << a << " "; cout << "\n" << endl;
     */
    if (vc[0] == vc[5]) {
        switch (vc[8]) {
            case 'A': if (vc[5] == vc[4]) return false; break;
            case 'B': if (vc[9] == vc[4]) return false; break;
            case 'C': if (vc[1] == vc[4]) return false; break;
            case 'D': if (vc[8] == vc[4]) return false; break;
        }
    }
    else {
        switch (vc[8]) {
            case 'A': if (vc[5] != vc[4]) return false; break;
            case 'B': if (vc[9] != vc[4]) return false; break;
            case 'C': if (vc[1] != vc[4]) return false; break;
            case 'D': if (vc[8] != vc[4]) return false; break;
        }
    }
    //10
    /*
     *cout << "\n\n\n10\n\n\n" ;
     *for (const auto &a:vc) cout << a << " "; cout << "\n" << endl;
     */
    int max_value = 1<<31;
    for (int i=0; i<4; ++i) {
        if (max_value < max_cnt[i]) max_value = max_cnt[i];
    }
    int result = max_value - min_value;
    switch (vc[9]) {
        case 'A': if (result != 3) return false; break;
        case 'B': if (result != 2) return false; break;
        case 'C': if (result != 4) return false; break;
        case 'D': if (result != 1) return false; break;
    }

    return true;
}
int main()
{
    vector<char> vc;
    vc.assign(11, 'A');

    while (vc.back() == 'A') {
        /*
         *for (const auto &c : vc) cout << c << " ";
         *cout << endl;
         */
        if (match(vc)) {
            cout << "find it" << endl;
            break;
        }
        inc(vc, 0);
    }

    for (auto i=vc.begin(); (i+1)!=vc.end(); ++i) cout << *i << " "; 
    cout << endl;

    return 0;
}
