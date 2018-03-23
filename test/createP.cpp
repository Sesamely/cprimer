/************************************************************************
****	> File Name:    	createP.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月12日 星期一 16时38分55秒
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

/*!!!!!use global var!!!!!!*/
int count = 0;

void createPailie(string &str, int begin, int end)
{
    if (begin == end) {
        cout << str << endl;
        ++count;
        return;
    }

    for (int i=begin; i<=end; ++i) {
        swap(str[begin], str[i]);
        createPailie(str, begin+1, end);
    }
}

int main()
{
    string str;
    cin >> str;
    createPailie(str, 0, str.length()-1);
    cout << count << endl;

    return 0;
}
