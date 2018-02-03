/************************************************************************
****	> File Name:    	test.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sat 03 Feb 2018 09:46:31 PM CST
************************************************************************/

#include "./adjacent_graph.h"

using namespace std;

int main()
{
    adjacent_list adj;
    get_adjacent_list(cin, adj);
    disp_adj(adj);

    return 0;
}
