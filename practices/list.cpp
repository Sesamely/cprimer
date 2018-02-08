/************************************************************************
****	> File Name:    	delete_node.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 05 Feb 2018 08:45:30 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode *m_pNext;
};

void delete_node(ListNode **phead, ListNode *to_delete)
{
    if (!to_delete || !phead) return;
    
    if (to_delete->m_pNext) {
        to_delete->m_nValue = to_delete->m_pNext->m_nValue;
        ListNode *real_delete = to_delete->m_pNext;
        to_delete->m_pNext = to_delete->m_pNext->m_pNext;
        delete real_delete;
    }
    else {
        ListNode *p_temp = *phead;
        if (p_temp == to_delete) {
            delete to_delete;
            *phead = p_temp = nullptr;
        }
        while (p_temp) {
            if (p_temp->m_pNext == to_delete) {
                p_temp->m_pNext = to_delete->m_pNext;
                delete to_delete;
                break;
            }
            p_temp = p_temp->m_pNext;
        }
    }
}

void disp(ListNode *head) {
    if (head == nullptr) return;
    ListNode *p = head;
    while(p) {
        cout << p->m_nValue << " ";
        p=p->m_pNext;
    }
    cout << endl;
}

void invert(ListNode **head) {
    if (head == nullptr) return;

    ListNode *temp = *head;
    ListNode *temp_head = nullptr, *temp_next;
    while (temp) {
        temp_next = temp->m_pNext;
        temp->m_pNext = temp_head;
        temp_head = temp;

        temp = temp_next;
    }
    *head = temp_head;
}

ListNode** merge(ListNode *head1, ListNode *head2) {
    if (!head1 || !head2) return nullptr;

    ListNode *merge_head = nullptr,
            *tail = nullptr,
            *use = nullptr,
            **result = nullptr;

    while (head1 && head2) {
        if (head1->m_nValue <= head2->m_nValue) {
            use = head1;
            head1 = head1->m_pNext;
        }
        else {
            use = head2;
            head2 = head2->m_pNext;
        }

        if (merge_head == nullptr) {
            merge_head = use;
            result = &merge_head;
            tail = use;
        }
        else {
            tail->m_pNext = use;
            tail = use;
        }
    }
    if (head1) {
        tail->m_pNext = head1;
    }
    else {
        tail->m_pNext = head2;
    }

    return result;
}

ListNode *create_list(vector<int> v_int) {
    ListNode *head=nullptr, *p_temp, *tail;

    for (const auto &v : v_int) {
        p_temp = new ListNode();
        p_temp->m_nValue = v;

        if (head) {
            tail->m_pNext = p_temp;
            tail = p_temp;
        }
        else {
            head = tail = p_temp;
        }
    }
    if (head) tail->m_pNext = nullptr;
    return head;
}
/*this algorithm is NOT effective*/
ListNode *first_common(ListNode *l1, ListNode *l2) {
    if (l1==nullptr || l2==nullptr) return nullptr;
    
    if (l1 == l2) return l1;
    else {
        ListNode *common = nullptr;
        common = first_common(l1->m_pNext, l2);
        if (!common) common = first_common(l1, l2->m_pNext);
        return common;
    }
}
ListNode *first_common_O_m(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr || l2 == nullptr) return nullptr;

    int l1_length=0, l2_length=0;
    ListNode *p;
    for (p=l1; p!=nullptr; p=p->m_pNext) ++l1_length;
    for (p=l2; p!=nullptr; p=p->m_pNext) ++l2_length;

    while (l1_length < l2_length) {
        if (l2->m_nValue == l1->m_nValue) return l2;
        else l2 = l2->m_pNext;
    }
    while (l1_length > l2_length) {
        if (l2->m_nValue == l1->m_nValue) return l1;
        else l1 = l1->m_pNext;
    }

    while (l1 && l2) {
        if (l1->m_nValue == l2->m_nValue) return l2;
        l1 = l1->m_pNext;
        l2 = l2->m_pNext;
    }

    return nullptr;
}
ListNode *first_value_discommon(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr && l2 == nullptr) return nullptr;
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    if (l1->m_nValue != l2->m_nValue)  return l1;
    else return first_value_discommon(l1->m_pNext, l2->m_pNext);
}

ListNode *ptr_of_value(int value, ListNode *root) {
    ListNode *p = root;
    while (p) {
        if (p->m_nValue == value) return p;
        p = p->m_pNext;
    }

    return nullptr;
}
void delete_list_recursive(ListNode *node) {
    if (node) {
        delete_list_recursive(node->m_pNext);
        cout << "delete " << node->m_nValue << endl;
        delete node;
    }
}
int main()
{
    int i ;
    vector<int> v_int, v_int1;

    while (cin >> i) {
        if (!i) break;
        v_int.push_back(i);
    }
    while (cin >> i) {
        if (!i) break;
        v_int1.push_back(i);
    }
    cin >> i; 

    ListNode *head, *head1;
    head = create_list(v_int);
    head1 = create_list(v_int1);

    /*
     *disp(head);
     *if (ptr_of_value(i, head)) {
     *    delete_list_recursive(ptr_of_value(i, head)->m_pNext);
     *    ptr_of_value(i, head)->m_pNext = ptr_of_value(i, head1);
     *}
     *disp(head);
     *disp(head1);
     *disp(first_common_O_m(head1, head));
     */

    return 0;
}

