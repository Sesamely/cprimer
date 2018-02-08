/*************************************************************************
	> File Name: 重建二叉树.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月22日 星期五 18时04分11秒
 ************************************************************************/

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

typedef struct Node {
    int             data;
    struct Node    *left;
    struct Node    *right;
}BinaryTree;

/*{{{*/
// Find the maximum height of the binary tree
int maxHeight(BinaryTree *p) {
  if (!p) return 0;
  int leftHeight = maxHeight(p->left);
  int rightHeight = maxHeight(p->right);
  return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Convert an integer value to string
string intToString(int val) {
  ostringstream ss;
  ss << val;
  return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
  deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
  deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? intToString((*iter)->data) : "");
    out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
  deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? intToString((*iter)->data) : "");
  }
  out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(BinaryTree *root, int level=1, int indentSpace=4, ostream& out=cout) {
  int h = maxHeight(root);
  int nodesInThisLevel = 1;

  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
    
  deque<BinaryTree*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

    for (int i = 0; i < nodesInThisLevel; i++) {
      BinaryTree *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
	      nodesQueue.push_back(currNode->left);
	      nodesQueue.push_back(currNode->right);
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}
/*}}}*/

BinaryTree *reconstrucrTree(vector<int> &pre,vector<int> &mid)/*{{{*/
{
    if(!pre.size()) return NULL;
    
    int i = 0;
    vector<int> tempPre1,tempMid1,tempPre2,tempMid2;
    BinaryTree *temp;

    temp = (BinaryTree *)malloc(sizeof(BinaryTree));
    temp->data = pre[0];
    while(mid[i] != pre[0]) {
        tempMid1.push_back(mid[i]);
        tempPre1.push_back(pre[++i]);
    }
    while(mid[i] != mid[mid.size()-1]) {
        tempMid2.push_back(mid[++i]);
        tempPre2.push_back(pre[i]);
    }
    temp->left = reconstrucrTree(tempPre1,tempMid1);
    temp->right = reconstrucrTree(tempPre2,tempMid2);

    return temp;
}/*}}}*/

void disp(BinaryTree *node)/*{{{*/
{
    if(node!=NULL) {
        cout << ' ' << node->data;
        disp(node->left);
        disp(node->right);
    }
}
void disp1(BinaryTree *node)
{
    if(node!=NULL) {
        disp1(node->left);
        cout << ' ' << node->data;
        disp1(node->right);
    }
}
void completeDisp(BinaryTree *node)
{
    disp(node);
    cout << endl;
    disp1(node);
    cout << endl;
}/*}}}*/

bool has_same_sub_structure(BinaryTree *root1, BinaryTree *root2) {
    if (root2 == nullptr) return true;
    if (root1 == nullptr) return false;

    if (root1->data != root2->data) return false;

    return has_same_sub_structure(root1->left, root2->left) &&
            has_same_sub_structure(root1->right, root2->right);
}
BinaryTree *find_same_structure(BinaryTree *demo, BinaryTree *sub) {
    if (demo == nullptr || sub == nullptr) return nullptr;

    BinaryTree *result_ptr = nullptr;
    bool result = false;
    if (demo->data == sub->data) {
        result_ptr = demo;
        result = has_same_sub_structure(demo, sub);
    }
    if (!result) {
        result_ptr = find_same_structure(demo->left, sub);
        if (result_ptr) result = true;
    }
    if (!result) 
        result_ptr = find_same_structure(demo->right, sub);

    return result_ptr;
}

BinaryTree *copy(BinaryTree *node) {
    if (!node) return nullptr;
    BinaryTree *temp_node = new BinaryTree();
    temp_node->data = node->data;
    temp_node->left = copy(node->left);
    temp_node->right = copy(node->right);

    return temp_node;
}
void mirror(BinaryTree *node) {
    if (!node) return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}
void mirror_iterative(BinaryTree *node) {
    while (node) {
        swap(node->left, node->right);
        mirror(node->left);
        node = node->right;
    }
}

/*this is not simple enough*/
BinaryTree *binaryTree_to_2direction_list(BinaryTree *node)
{
    if (node == nullptr) return nullptr;

    BinaryTree *left_head, *left_tail, *right_head, *right_tail;

    left_head = binaryTree_to_2direction_list(node->left);
    right_head = binaryTree_to_2direction_list(node->right);

    if (left_head == nullptr && right_head != nullptr) {
        right_tail = right_head->left;

        node->right = right_head; 
        node->left = right_tail;
        right_head->left = node;
        right_tail->right = node;

        return node;
    }
    else if (right_head == nullptr && left_head != nullptr) {
        left_tail = right_head->left;
        node->right = left_head;
        node->left = left_tail;
        left_tail->right = node;
        left_head->left = node;

        return left_head;
    }
    else if (left_head == nullptr && right_head == nullptr) {
        node->left = node->right = node;

        return node;
    }
    else {
        left_tail = left_head->left;
        right_tail = right_head->left;

        node->left = left_tail;
        node->right = right_head;
        left_tail->right = node;
        right_head->left = node;
        left_head->left = right_tail;
        right_tail->right = left_head;

        return left_head;
    }
}
void ConvertNode(BinaryTree *p_node, BinaryTree **p_last_node_in_list) {
    if (!p_node) return;

    BinaryTree *p_cur = p_node;

    ConvertNode(p_node->left, p_last_node_in_list);
    p_cur->left = *p_last_node_in_list;
    if (*p_last_node_in_list) (*p_last_node_in_list)->right = p_cur;

    *p_last_node_in_list = p_cur;
    ConvertNode(p_node->right, p_last_node_in_list);
}
BinaryTree * Convert(BinaryTree *p_root_of_tree) {
    BinaryTree *p_last_node_in_list = nullptr;
    ConvertNode(p_root_of_tree, &p_last_node_in_list);

    BinaryTree *p_head_of_list = p_last_node_in_list;
    while (p_head_of_list != nullptr && p_head_of_list->left != nullptr) 
        p_head_of_list = p_head_of_list->left;

    return p_head_of_list;
}
void disp_2d_list(BinaryTree *root) {
    if (!root) return;
    BinaryTree *node = root;
    cout << node->data << " ";
    node = node->right;
    while (node && node != root) {
        cout << node->data << " ";
        node = node->right;
    }
    cout << endl;
}

void disp_depth_of(BinaryTree *node, int &depth)
{
    if (node == nullptr) {
        depth = -1;
        return;
    }
    int left_depth, right_depth;
    disp_depth_of(node->left, left_depth);
    disp_depth_of(node->right, right_depth);

    depth = left_depth > right_depth ? left_depth + 1 : right_depth + 1;
    cout << "value is: " << node->data << " and depth is: " << depth << endl; 
}

int main()
{
    vector<int> pre, mid;
    int i;
    while (cin >> i) {
        if (!i) break;
        pre.push_back(i);
    }
    while (cin >> i) mid.push_back(i);
    BinaryTree *root = reconstrucrTree(pre,mid);

    printPretty(root);
    disp_2d_list(Convert(root));

    return 0;
}
