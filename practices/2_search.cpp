/*************************************************************************
	> File Name: twothSearch.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月22日 星期五 20时21分13秒
 ************************************************************************/
#include<vector>
#include<iostream>
using namespace std;

vector<int> array{1,2,3,4,5,6,19,80,1023};

int circulation(vector<int> &array, int value)
{
    int i=0,j=array.size()-1,mid;
    while(i<=j)
    {
        mid = (i + j) / 2;
        //cout << array[mid] << endl;
        if (array[mid] == value) return mid;
        if(array[mid] < value) i = mid + 1;
        else j = mid - 1;
    }
    return -1;
}

int iteration(vector<int> &array, int beg, int end, int value)
{
    if(beg > end) return -1;

    int mid = (beg+end) / 2;
    //cout << array[mid] << endl;
    if(array[mid] == value)
        return mid;
    if(array[mid] < value)
        return iteration(array,mid+1,end,value);
    else
        return iteration(array,beg,mid-1,value);
}

int main()
{
    int loc, value;
    cin >> value;
    loc = circulation(array,value);
    //loc = iteration(array,0,array.size()-1,value);
    if (loc!=-1)
        cout << "The location of the " << value << " in global array is " << loc << ", value is " << array[loc] << endl; 
    else
        cout << value << " NOT IN global array..." << endl; 
    return 0;
}
