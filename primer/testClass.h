/************************************************************************
****	> File Name:    	testClass.h
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 09:10:33 PM CST
************************************************************************/

#ifndef _TESTCLASS_H
#define _TESTCLASS_H

#include <string>
using namespace std;

class TreeNode {
public:
    TreeNode() : 
        value(""), count(0), left(nullptr), right(nullptr) {}
    TreeNode(const string &str) :
        value(str), count(0), left(nullptr), right(nullptr) {}
    //copy constructor
    TreeNode(const TreeNode &tn) :
        value(tn.value), count(tn.count), left(tn.left), right(tn.right) {}
    //destructor
    ~TreeNode() {
        if (left) delete left;
        if (right) delete right;
    }
    //copy-assignment operator
    /*
     *TreeNode &operator=(const TreeNode &tn) {
     *    
     *}
     */
private:
    string      value;
    int         count;
    TreeNode    *left;
    TreeNode    *right;
};

class BinStrTree {
private:
    TreeNode *root;
};

#endif
