/************************************************************************
 ****	> File Name:    	addTowNumbers.cpp
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月20日 星期五 20时43分35秒
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head=NULL, *tail, *temp_node;
        int cin = 0, add1, add2, temp;
        while (l1!=NULL || l2!=NULL) {
            if (l1) {
                add1 = l1->val;
                l1 = l1->next;
            } else {
                add1 = 0;
            }
            if (l2) {
                add2 = l2->val;
                l2 = l2->next;
            } else {
                add2 = 0;
            }
    
            temp = add1 + add2 + cin;
            //cout << temp << " = " << add1 << " + " << add2 << " + " << cin << endl;
            cin = 0;
            if (temp > 9) {
                temp -= 10;
                cin = 1;
            } 
            
            temp_node = new ListNode(temp);
            if (head == NULL) {
                head = temp_node;
            } else {
                tail->next = temp_node;
            }
            tail = temp_node;
        }    
        if (cin) {
            tail->next = new ListNode(1);
        }

        return head;
    }
};

int main()
{
    ListNode *l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode *l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    Solution s;
    ListNode *head = s.addTwoNumbers(l1, l2);;
    while (head) {
        cout << head->val << (head->next ? " -> " : "\n");
        head = head->next;
    };

    return 0;
}
