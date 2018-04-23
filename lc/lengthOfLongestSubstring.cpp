/************************************************************************
 ****	> File Name:    	lengthOfLongestSubstring.cpp
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月20日 星期五 21时08分51秒
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i=0, j=0, maxlength=0;
        const int S_LEN = s.length();

        for (j=0; j<S_LEN; ++j) {
            int temp_i = i;
            for (; temp_i<j; ++temp_i) {
                if (s[temp_i] == s[j]) {
                    i = temp_i + 1;
                    break;
                }
            }
            //cout << i << " " << j << endl;

            if (j-i+1 > maxlength) {
                maxlength = j-i+1;
            }
        }

        return maxlength;
    }
};

int main(void) {
    Solution s;
    string str; 
    cin >> str;
    cout << s.lengthOfLongestSubstring(str) << endl;

    return 0;
}
