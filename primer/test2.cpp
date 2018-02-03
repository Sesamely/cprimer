/************************************************************************
****	> File Name:    	test2.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 20 Jan 2018 02:24:31 PM CST
************************************************************************/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<string>
#include<vector>
#include<list>
#include<iterator>
#include<map>

using namespace std;
using namespace std::placeholders;

bool foo(const string &str, string::size_type sz) {
    if (str.size() <= sz) {
        cout << str << ' ';
        return true;
    }
    return false;
}
void foo_copy(vector<string> &strVec, list<string> &strList) {
    //auto iter = back_inserter(strList);
    //auto iter = front_inserter(strList);
    auto iter = inserter(strList, strList.end());
    stable_sort(strVec.begin(), strVec.end());
    unique_copy(strVec.cbegin(), strVec.cend(), iter);
}

int main1()
{
    vector<string> str_vec{"liu","yi","wen","123","456","fox","fire","chrome","fox","liu","wen"};
    list<string> str_list;

    foo_copy(str_vec, str_list);

    for_each(str_list.cbegin(), str_list.cend(), [](const string &s){ cout << s << ' '; }); cout << endl;

    return 0;
}
pair<string, int> foo2(const string &str) {
    auto p = make_pair(str, str.size());
    cout << reinterpret_cast<long>(&p) << '\n';
    return p;
}

std::string testString(const char *str) {
    return string(str);
}

int main() {

    string s = testString("liuyiwen");
    cout << s << endl;
    return 0;
}
