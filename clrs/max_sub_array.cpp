/************************************************************************
****	> File Name:    	max_sub_array.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 29 Jan 2018 09:43:02 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <cassert>
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
    
    if (left.sum >= right.sum && left.sum >= across_mid.sum) return left;
    else if (right.sum >= left.sum && right.sum >= across_mid.sum) return right;
    return across_mid;
}

area find_max_sub_array_O_n(vector<int> array, int begin, int end)
{
    area a;
    if (begin > end) return a;
    int i, next_begin=0, sum=0;

    a.sum = 1<<31;
    for (i=0; i<=end-begin; ++i) {
        sum += array[i];
        if (a.sum < sum) {
            a.sum = sum;
            a.end = i;
            a.begin = next_begin;
        }
        if (sum<0 && i!=end-begin) {
            a.sum = 1<<31;
            sum = 0;
            next_begin = i+1;
        }
    }
    return a;
}

int find_max_sub_array_dp_aux(const vector<int> &a, int i, 
                              vector<int> &c,
                                vector<int> &s) 
{
    assert(i>=0);
    if (c[i] != -1) return c[i];
    if (i==0) {
        c[0] = a[0];
        return c[i];
    }

    int pre = find_max_sub_array_dp_aux(a, i-1, c, s);
    if (pre<=0) {
        c[i] = a[i];
    }
    else {
        c[i] = a[i] + pre;
        s[i] = s[i-1] + 1;
    }

    return c[i];
}
void find_max_sub_array_dp(vector<int> a) {
    vector<int> c, s;
    c.assign(a.size(), -1);
    s.assign(a.size(), 1);

    find_max_sub_array_dp_aux(a, a.size()-1, c, s);

    int max = 1<<31, max_loc = -1;
    for (int i=0; i<int(c.size()); ++i) {
        if (c[i] > max) {
            max = c[i];
            max_loc = i;
        }
    }
    if (max_loc != -1) {
        cout << "max is: " << max
            << "\trange is: [ " << max_loc-s[max_loc]+1
            << " , " << max_loc << " ]" << endl;
    }    
    else cout << "empty array!" << endl;
}

int main1()
{
    int integer;
    vector<int> array;
    array.reserve(100);
    while(cin >> integer) array.push_back(integer);
    
    //area a=find_max_sub_array_O_n(array, 0, array.size()-1);
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
int main()
{
    vector<int> a;
    int i;
    while (cin >> i) a.push_back(i);

    find_max_sub_array_dp(a);

    return 0;
}
