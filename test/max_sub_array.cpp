/************************************************************************
****	> File Name:    	max_sub_array.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 29 Jan 2018 09:43:02 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

struct area {
    int begin;
    int end;
    int sum;
};

area find_across_mid(const vector<int> &array, int begin, int mid, int end)
{
    area temp;
    int i, sum, left_index, right_index, left_max_sum, right_max_sum;
    left_max_sum = right_max_sum = 1<<31;
    sum = 0;
    for (i=mid; i>=begin; --i) {
        sum += array[i];
        if (sum > left_max_sum) {
            left_max_sum = sum;
            left_index = i;
        }
    }
    sum = 0;
    for (i=mid; i<=end; ++i) {
        sum += array[i];
        if (sum > right_max_sum) {
            right_max_sum = sum;
            right_index = i;
        }
    }
    temp.begin = left_index;
    temp.end = right_index;
    temp.sum = left_max_sum + right_max_sum - array[mid];
    return temp;
}

area find_max_sub_array(const vector<int> &array, int begin, int end)
{
    area left, right, across_mid;
    if (begin == end) {
        left.begin = left.end = begin;
        left.sum = array[begin];
        return left;
    }
    int mid = (begin + end) >> 1;
    left = find_max_sub_array(array, begin, mid);
    right = find_max_sub_array(array, mid+1, end);
    across_mid = find_across_mid(array, begin, mid, end);
    
    if (left.sum > right.sum && left.sum > across_mid.sum) return left;
    else if (right.sum > left.sum && right.sum > across_mid.sum) return right;
    return across_mid;
}

int main()
{
    int integer;
    vector<int> array;
    array.reserve(100);
    while(cin >> integer) array.push_back(integer);
    
    area a=find_max_sub_array(array, 0, array.size()-1);

    integer = 0;
    for (int i = 0; i<static_cast<int>(array.size()); ++i) {
        if (i == a.begin) cout << "{";
        cout << array[i];
        if (i == a.end) cout << "} ";
        else cout << " ";
        ++integer;
        if (integer % 20 == 0) cout << endl;
    }
    cout << "\nleft boundary is: " << a.begin << ". right boundary is: " << a.end
        << ". max_sub_array's sum is: " << a.sum << "." << endl;

    return 0;
}

