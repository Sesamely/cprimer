/************************************************************************
 ****	> File Name:    	twoSum.cpp
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月20日 星期五 19时41分22秒
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> demo = nums;
        quick_sort(nums, 0, nums.size()-1);
        for (const auto &a : nums) cout << a << " "; cout << endl;
        int i, j, size=nums.size();

        for (i=0; i<size; ++i) {
            if ( (j=find(nums, 0, size-1, target-nums[i], i)) != -1 ) {
                int r1 = find_loc_ex(demo, nums[i], -1),
                    r2 = find_loc_ex(demo, nums[j], r1);
                return {r1<r2 ? r1 : r2, r1>r2 ? r1 : r2};
            }
        }
        return {};
    }
private:
    int find_loc_ex(vector<int> &demo, int target, int ex) {
        int i, size = demo.size();
        for (i=0; i<size; ++i) {
            if (demo[i] == target && i != ex) 
                return i;
        }
        return -1;
    }

    int partition(vector<int> &v, int first, int back) {
        int i=first-1, j=first, last = v[back];
        for (; j<=back; j++) {
            if (v[j] <= last) {
                i++;
                swap(v[i], v[j]);
            }
        }
        return i;
    }

    void quick_sort(vector<int> &nums, int first, int back) {
        if (first >= back) return;
        int p= partition(nums, first, back);
        quick_sort(nums, first, p-1);
        quick_sort(nums, p+1, back);
    }

    int find(vector<int> &nums, int i, int j, int target, int ex) {
        cout << nums[i] << " " << nums[j] << " " << nums[(i+j)/2] << endl;
        if (i>j) return -1;
        int mid = (i + j) / 2;
        if (nums[mid] == target && mid == ex) {
            int size = nums.size() - 1;
            if (mid+1 <= size && nums[mid+1]==target) return mid+1;
            if (mid-1 >= 0 && nums[mid-1]==target) return mid-1;
            return -1;
        }
        if (nums[mid] == target && mid != ex) return mid;

        if (target < nums[mid]) return find(nums, i, mid-1, target, ex);
        else return find(nums, mid+1, j, target, ex);
    }
};

int main(void)
{
    Solution s;
    vector<int> v = {3, 2, 4};
    vector<int> result = s.twoSum(v, 6);
    cout << result[0] << " " << result[1] << endl;

    return 0;
}
