/************************************************************************
****	> File Name:    	count_sort.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sun 04 Feb 2018 05:29:26 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void count_sort(const vector<int> &A, vector<int> &sort_A)
{
    int i;
    vector<int> C;
    sort_A.assign(A.size(),0);
    auto MAX_ELEMENT_OF_A = max_element(A.cbegin(), A.cend());
    auto MIN_ELEMENT_OF_A = min_element(A.cbegin(), A.cend());
    if (*MIN_ELEMENT_OF_A < 0) {
        throw out_of_range("A CANNOT include negative number!");
    }
    C.assign(*MAX_ELEMENT_OF_A+1 ,0);

    for (const auto &i : A) {
        ++C[i];
    }
    for (i=1; i<*MAX_ELEMENT_OF_A+1; ++i) {
        C[i] += C[i-1];
    }

    for (i=A.size()-1; i>=0; --i) {
        sort_A[C[A[i]]] = A[i];
        --C[A[i]];
    }
}

int main()
{
    int i;
    vector<int> A, sort_A;
    while (cin >> i) A.push_back(i);

    count_sort(A, sort_A);

    for (const auto &i : sort_A) cout << i << " ";
    cout << endl;

    return 0;
}
