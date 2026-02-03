class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if (n < 4) return false;

        int i = 0;

        // 1) strictly increasing
        while (i + 1 < n && nums[i] < nums[i + 1]) i++;
        int p = i;
        if (p == 0) return false;              // no increasing part

        // 2) strictly decreasing
        while (i + 1 < n && nums[i] > nums[i + 1]) i++;
        int q = i;
        if (q == p) return false;              // no decreasing part
        if (q == n - 1) return false;          // no final increasing part

        // 3) strictly increasing till end
        while (i + 1 < n && nums[i] < nums[i + 1]) i++;

        return i == n - 1;
    }
};
