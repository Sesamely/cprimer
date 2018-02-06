/************************************************************************
****	> File Name:    	delete_node.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 05 Feb 2018 08:45:30 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode *m_pNext;
};

void disp(ListNode **head) {
    ListNode *p = *head;
    while(p) {
        cout << p->m_nValue << " ";
        p=p->m_pNext;
    }
    cout << endl;
}

int main()
{
    int i;
    vector<int> v_int;

    while (cin >> i) v_int.push_back(i);

    ListNode **head=nullptr, *p_temp=nullptr;

    for (auto i=v_int.begin(); i!=v_int.end(); ++i) {
        p_temp = new ListNode();
        p_temp->m_nValue = *i;

        if (head) {
            p_temp->m_pNext = *head;
            head = &p_temp;
        }
        else {
            p_temp->m_pNext = nullptr;
            head = &p_temp;
        }
    }
    
    disp(head);

    return 0;
}


