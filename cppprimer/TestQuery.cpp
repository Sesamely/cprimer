/************************************************************************
****	> File Name:    	TestQuery.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 12:00:37 PM CST
************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <memory>
using namespace std;
 
class QueryResult {
public:
private:
    int count = 0;   
};

class TextQuery {
    using line_type = unsigned int;
public:
    TextQuery() {}
    TextQuery(istream& infile);
    QueryResult query(string s);
private:
    vector<string> text;
    map<string, set<line_type>> map;
};
TextQuery::TextQuery(istream& infile) {
    string s;
    while (getline(infile, s)) {
        text.push_back(s);
    }
}
QueryResult TextQuery::query(string demo_str) {
    line_type number;
    string temp_str;
    for (auto index=text.cbegin(); index != text.cend(); ++index) {
        istringstream in(*index);    
        while (in >> temp_str) {
            
        }
    }
}
