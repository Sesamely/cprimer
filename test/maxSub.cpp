/************************************************************************
****	> File Name:    	endSub.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 27 Jan 2018 08:35:59 PM CST
************************************************************************/

#include<iostream>
using namespace std;

template <typename loc_type, typename sum_type> 
class area {
public:
    loc_type begin;
    loc_type end;
    sum_type sum;
};

template <typename seq_type, typename loc_type, typename sum_type> 
area<loc_type, sum_type> find_across_mid(seq_type S, loc_type begin, loc_type end, loc_type mid)
{
    area<loc_type, sum_type> a;
    a.begin = a.end = mid;
    a.sum = S[mid];
    loc_type i;
    for (i=mid; i--!=begin; i!=end) {}
}
