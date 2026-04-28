class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {

        vector<int> nums;

        for (auto &row : grid)
            for (int v : row)
                nums.push_back(v);

        int rem = nums[0] % x;

        for (int v : nums) {
            if (v % x != rem)
                return -1;
        }

        sort(nums.begin(), nums.end());

        int med = nums[nums.size() / 2];

        long long ans = 0;

        for (int v : nums)
            ans += abs(v - med) / x;

        return (int)ans;
    }
};