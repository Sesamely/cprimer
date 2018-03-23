/************************************************************************
****	> file name:    	knapsack.cpp
****	> author:       	yiwen liu
****	> mail:         	newiyuil@163.com
****	> created time: 	2018年03月12日 星期一 14时29分44秒
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int capacity, i, j;
    vector<int> v, c;

    cin >> capacity;
    v.push_back(0);
    c.push_back(0);
    while (cin >> i) {
        if (!i) break;
        c.push_back(i);
    }
    while (cin >> i) {
        v.push_back(i);
    }

    int ROW = v.size(),
        COL = capacity + 1;
    int V[ROW][COL];

    for (i=0; i<ROW; ++i)
        V[i][0] = 0;
    for (j=0; j<COL; ++j)
        V[0][j] = 0;

    for (i=1; i<ROW; ++i) {
        for (j=1; j<COL; ++j) {
            V[i][j] = V[i-1][j];
            if (j >= c[i]) {
                int value = V[i-1][j-c[i]] + v[i];
                if (value > V[i][j]) V[i][j] = value;
            }
        }
    }

    for (i=0; i<ROW; ++i) {
        for (j=0; j<COL; ++j) {
            cout << V[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;

    return 0;
}
