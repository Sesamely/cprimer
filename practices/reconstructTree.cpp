/*************************************************************************
	> File Name: 重建二叉树.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月22日 星期五 18时04分11秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

typedef struct Node {
    int             m_nValue;
    struct Node    *my_pLeft;
    struct Node    *my_pRight;
}BinaryTreeNode;

BinaryTreeNode *reconstrucrTree(vector<int> &pre,vector<int> &mid)
{
    if(!pre.size()) return NULL;
    
    int i = 0;
    vector<int> tempPre1,tempMid1,tempPre2,tempMid2;
    BinaryTreeNode *temp;

    temp = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    temp->m_nValue = pre[0];
    while(mid[i] != pre[0]) {
        tempMid1.push_back(mid[i]);
        tempPre1.push_back(pre[++i]);
    }
    while(mid[i] != mid[mid.size()-1]) {
        tempMid2.push_back(mid[++i]);
        tempPre2.push_back(pre[i]);
    }
    temp->my_pLeft = reconstrucrTree(tempPre1,tempMid1);
    temp->my_pRight = reconstrucrTree(tempPre2,tempMid2);

    return temp;
}

void disp(BinaryTreeNode *node)
{
    if(node!=NULL) {
        cout << ' ' << node->m_nValue;
        disp(node->my_pLeft);
        disp(node->my_pRight);
    }
}
void disp1(BinaryTreeNode *node)
{
    if(node!=NULL) {
        disp1(node->my_pLeft);
        cout << ' ' << node->m_nValue;
        disp1(node->my_pRight);
    }
}
void completeDisp(BinaryTreeNode *node)
{
    disp(node);
    cout << endl;
    disp1(node);
    cout << endl;
}
int main()
{
    vector<int> pre{1,2,4,7,3,5,6,8};
    vector<int> mid{4,7,2,1,5,3,8,6};
    BinaryTreeNode *root = reconstrucrTree(pre,mid);
    completeDisp(root);
    return 0;
}
