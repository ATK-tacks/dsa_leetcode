class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int num = nums[i];

            // ❌ No solution if num is even
            if ((num & 1) == 0) {
                ans[i] = -1;
                continue;
            }

            // Minimum x such that x | (x + 1) == num
            int lowestBit = (num + 1) & -(num + 1);
            ans[i] = num - (lowestBit >> 1);
        }
        return ans;
    }
};