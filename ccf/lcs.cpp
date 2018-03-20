/************************************************************************
****	> File Name:    	lcs_array.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月14日 星期三 11时02分39秒
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int lcs(int i, int j, const string &s1, const string &s2, vector<vector<int>> &lcs_array)
{
    if (i<0 || j<0) return 0;
    if (lcs_array[i][j] != 0) return lcs_array[i][j];

    if (s1[i] == s2[j]) {
        lcs_array[i][j] = lcs(i-1, j-1, s1, s2, lcs_array) + 1;
        return lcs_array[i][j];
    }
    
    lcs_array[i][j] = lcs(i-1, j, s1, s2, lcs_array) > lcs(i, j-1, s1, s2, lcs_array) ?
        lcs(i-1, j, s1, s2, lcs_array) : lcs(i, j-1, s1, s2, lcs_array);

    return lcs_array[i][j];
}

void disp_according_lcs_array(int i, int j, const vector<vector<int> > &lcs, const string &s_demo)
{
    if (i-1<0 || j-1<0)  {
        if (lcs[i][j] == 1) {
            if (i==0 && j==0) cout << s_demo[j] << " ";
            else {
                if (i==0) {
                    if (lcs[i][j-1] == 0) cout << s_demo[j] << " ";
                    else disp_according_lcs_array(i, j-1, lcs, s_demo);
                }
                else {
                    if (lcs[i-1][j] == 0) cout << s_demo[j] << " ";
                    else disp_according_lcs_array(i-1, j, lcs, s_demo);
                }
            }
        }
        return ;
    }
    if (lcs[i][j] == lcs[i-1][j])
        disp_according_lcs_array(i-1, j, lcs, s_demo);
    else if (lcs[i][j] == lcs[i][j-1])
        disp_according_lcs_array(i, j-1, lcs, s_demo);
    else if (lcs[i][j] == lcs[i-1][j-1] + 1) {
        disp_according_lcs_array(i-1, j-1, lcs, s_demo);
        cout << s_demo[j] << " ";
    }
}

int main()
{
    string s1, s2;
    cin >> s1 ;
    cin >> s2;
    int ROW = s1.length(), COL = s2.length();
    vector<vector<int> > lcs_array;
    vector<int> temp_v;
    temp_v.assign(COL, 0);
    lcs_array.assign(ROW, temp_v);

    cout << lcs(ROW-1, COL-1, s1, s2, lcs_array) << endl;
    /*
     *for (int i=0; i<COL; ++i) {
     *    if (lcs_array[0][i] == 1) {
     *        cout << s2[i] << " ";
     *        break;
     *    }
     *}
     */
    disp_according_lcs_array(ROW-1, COL-1, lcs_array, s2);
    cout << endl;
    /*
     *for (auto &v : lcs_array) {
     *    for (auto &a : v) {
     *        cout << a << " ";
     *    }
     *    cout << endl;
     *}
     */

    return 0;
}

