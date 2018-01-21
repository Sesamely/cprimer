/************************************************************************
****	> File Name:    	memory.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sun 21 Jan 2018 12:59:05 PM CST
************************************************************************/

#include "./cmemory.h"
#include <fstream>
#include <sstream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "usage: elf filename" << endl;
        return -1;
    }

    ifstream in(argv[1]);
    if (!in.good()) {
        cout << "file open failure!" << endl;
        return -2;
    }

    string line, word;
    while(getline(in, line)) {
        StrBlob strb;
        istringstream l(line);
        while(l >> word) { strb.push_back(word); }
        StrBlobPtr spend(strb.end());
        for(auto i=strb.begin(); !i.curr_equal(spend); i=i.incr()) {
            cout << i.deref() << ' ';
        }
        cout << endl;
    }
    return 0;
}
