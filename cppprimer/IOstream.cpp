/************************************************************************
****	> File Name:    	IOstream.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Wed 10 Jan 2018 11:41:57 PM CST
************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

vector<string> str;

int main(int argc,char **argv)
{
    if (argc < 2) {
        cout << "Uage: exec filename [filename...]" << endl;
        return 0;
    }
    for(auto p=argv+1; p!=argv+argc; ++p) {
        ifstream in(*p);
        if(in) {
            string line;
            while(getline(in, line)) {
                str.push_back(line);
            }
            /*
             *string word;
             *while(in >> word) {
             *    str.push_back(word);
             *}
             */
            str.push_back("");
        }
        else {
            cout << "error!" << endl;
            return -1;
        }
    }
    cout << '\n';
    int row=0;
    for (auto i=str.begin(); i!=str.end(); i++) {
        cout << ++row << "\tRow is " << *i << '\n';
        //cout << *i << ' ';
    }
    cout << endl;
    return 0;
}
