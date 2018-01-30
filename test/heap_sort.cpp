/************************************************************************
****	> File Name:    	heap_sort.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Tue 30 Jan 2018 12:42:27 PM CST
************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

inline int left_child(int i)
{
    return (i*2);
}
inline int right_child(int i)
{
    return (i*2 + 1);
}
inline int parent(int i)
{
    return (i / 2);
}
/*数组小根堆*/
void min_heapify_recurse(vector<int> &v, int i, int size)
{
    if (i > parent(size)) return;

    int least_loc=i,
        i_left_child=left_child(i),
        i_right_child=right_child(i);

    if (i_left_child <= size && 
        v[i_left_child] < v[least_loc]) 
            least_loc = i_left_child;
    if (i_right_child <= size &&
             v[i_right_child] < v[least_loc]) 
                least_loc = i_right_child;

    if (least_loc != i) {
        swap(v[i], v[least_loc]);
        min_heapify_recurse(v, least_loc, size);
    }
}
void create_min_heap(vector<int> &v)
{
    int node = parent(v.size()-1);
    for (; node >= 1; --node) min_heapify_recurse(v, node, v.size()-1);
}

/*数组大根堆*/
/*size指向v中最后一个element, v中第一个element位置为1*/
void max_heapify_iterate(vector<int> &v, int i, int size)
{
    int largest_loc=i, i_left_child, i_right_child;
    while (i <= parent(size)) {
        i_left_child = left_child(i);
        i_right_child = right_child(i);
        
        if (i_left_child <= size && 
            v[i_left_child] > v[largest_loc]) 
                largest_loc = i_left_child;
        if (i_right_child <= size &&
                 v[i_right_child] > v[largest_loc]) 
                    largest_loc = i_right_child;

        if (largest_loc != i) {
            swap(v[i], v[largest_loc]);
            i = largest_loc;
        }
        else break;
    }
}

void create_max_heap(vector<int> &v)
{
    int node;
    for (node = parent(v.size()-1); node >= 1; --node) {
        max_heapify_iterate(v, node, v.size()-1);
    }
}

void max_heap_sort(vector<int> &v)
{
    int last= v.size()-1;
    create_max_heap(v);
    while (last > 1) {
        swap(v[1], v[last]);
        --last;
        max_heapify_iterate(v, 1, last);
    }
}

void min_heap_sort(vector<int> &v)
{
    int last= v.size()-1;
    create_min_heap(v);
    while (last > 1) {
        swap(v[1], v[last]);
        --last;
        min_heapify_recurse(v, 1, last);
    }
}

/*以下为priority queue*/
int heap_max(const vector<int> &v) {return v[1];}

int heap_extract_max(vector<int> &v)
{
    if (static_cast<int>(v.size()) - 1  <= 0) throw out_of_range("heap is empty");
    int max = v[1];
    v[1] = v[v.size()-1];
    v.erase(--v.end());
    max_heapify_iterate(v, 1, v.size()-1);
    return max;
}

void heap_increase_key(vector<int> &v, int i, int key)
{
    if (i<1 || i>static_cast<int>(v.size()-1)) 
        throw out_of_range("insert i is out of range");
    if (key < v[i]) {
        cout << "add key is litter than v[i], NO ACTION!" << endl;
        return;
    }
    v[i] = key;
    int current = i;
    while (current > 1 && v[current]>v[parent(i)]) {
        swap(v[i], v[parent(i)]);
        current = parent(current);
    }
}

void max_heap_insert(vector<int> &v, const int key)
{
    v.push_back(1<<31);
    heap_increase_key(v, v.size()-1, key);
}

inline void create_max_heap_insert(const vector<int> &v_demo, vector<int> &v_result)
{
    for(const auto &i : v_demo) max_heap_insert(v_result, i);
}


int main()
{
    int i, j;
    vector<int> v, v1;
    while(cin >> i) v.push_back(i);

    v1.push_back(~(1<<31));
    create_max_heap_insert(v, v1);

    v.insert(v.begin(), ~(1<<31));
    create_max_heap(v);

    v1.erase(v1.begin());
    for(const auto &i : v) cout << i << ' '; cout << endl;
    for(const auto &i : v1) cout << i << ' '; cout << endl;

    cout << '\n';
    int len = v.size();
    for (j = 1; j<len; ++j) {
        for(const auto &i : v) cout << i << ' '; cout << endl;
        heap_extract_max(v);
    }
    return 0;
}
