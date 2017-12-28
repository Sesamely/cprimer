#include <deque>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>
#include <iostream>
#define _LIB_
#include "head.h"

void disp()
{
    cout << "Operator     is: " << Operator << endl;
    cout << "Identifier   is: " << Identifier << endl;
    cout << "Number       is: " << Number << endl;
    cout << endl;
}

void dispExpress1(ExprAST *node)
{
    if (node!=NULL&&typeid(*node)==typeid(BinaryExprAST)) {
        cout << ((BinaryExprAST*)node)->op ;
        dispExpress1(((BinaryExprAST*)node)->LHS);
        dispExpress1(((BinaryExprAST*)node)->RHS);
    }
    if(node!=NULL&&typeid(*node)==typeid(NumberExpr)) {
        cout << ((NumberExpr*)node)->value ;
    }
    if(node!=NULL&&typeid(*node)==typeid(VariableExprAST)) {
        cout << ((VariableExprAST*)node)->Name ;
    } 
}
void dispExpress2(ExprAST *node)
{
    if (node!=NULL&&typeid(*node)==typeid(BinaryExprAST)) {
        dispExpress2(((BinaryExprAST*)node)->LHS);
        cout << ((BinaryExprAST*)node)->op ;
        dispExpress2(((BinaryExprAST*)node)->RHS);
    }
    if(node!=NULL&&typeid(*node)==typeid(NumberExpr)) {
        cout << ((NumberExpr*)node)->value ;
    }
    if(node!=NULL&&typeid(*node)==typeid(VariableExprAST)) {
        cout << ((VariableExprAST*)node)->Name ;
    } 
}
void dispExpressPre(ExprAST *node) {
    dispExpress1(node);
    cout << endl ;
}
void dispExpressMid(ExprAST *node) {
    dispExpress2(node);
    cout << endl;
}

int maxDepthOf(ExprAST *node)
{
    if(!node) return 0;
    if(typeid(*node)==typeid(NumberExpr)|| \
        typeid(*node)==typeid(VariableExprAST)) return 1;
    int leftDepth = maxDepthOf(((BinaryExprAST*)node)->LHS);
    int rightDepth = maxDepthOf(((BinaryExprAST*)node)->RHS);
    return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
}

//Print the arm branches (eg / \) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<ExprAST*>& nodesQueue, ostream& out) {
    deque<ExprAST*>::const_iterator iter = nodesQueue.begin(); 
    for (int i = 0; i < nodesInThisLevel/2; i++) {
        out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << endl;
}

ExprAST* hasChild(ExprAST *node,string LR)
{
    if(!node) return NULL;
    if(typeid(*node)==typeid(BinaryExprAST)) {
        if(!LR.compare("left")&&((BinaryExprAST*)node)->LHS!=NULL) return (new ExprAST());
        if(!LR.compare("right")&&((BinaryExprAST*)node)->RHS!=NULL) return (new ExprAST());
    }
    return NULL;
}
string dispExprASTNode(ExprAST *node) 
{
    if(!node) return NULL;
    if(typeid(*node)==typeid(BinaryExprAST)) return string(1,((BinaryExprAST*)node)->op);
    else if(typeid(*node)==typeid(NumberExpr)) {
        std::ostringstream strs;
        strs << ((NumberExpr*)node)->value;
        return strs.str();
    }
    else if(typeid(*node)==typeid(VariableExprAST)) return ((VariableExprAST*)node)->Name;
    return NULL;
}
// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<ExprAST*>& nodesQueue, ostream& out) {
  deque<ExprAST*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && hasChild(*iter,"left")) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? dispExprASTNode(*iter) : "");
    out << ((*iter && hasChild(*iter,"right")) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<ExprAST*>& nodesQueue, ostream& out) {
  deque<ExprAST*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? dispExprASTNode(*iter): "");
  }
  out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(ExprAST *root, int level, int indentSpace, ostream& out) {
  int h = maxDepthOf(root);
  int nodesInThisLevel = 1;

  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
    
  deque<ExprAST*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

    for (int i = 0; i < nodesInThisLevel; i++) {
      ExprAST *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode&&(typeid(*currNode)==typeid(BinaryExprAST))) {
	      nodesQueue.push_back(((BinaryExprAST*)currNode)->LHS);
	      nodesQueue.push_back(((BinaryExprAST*)currNode)->RHS);
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





