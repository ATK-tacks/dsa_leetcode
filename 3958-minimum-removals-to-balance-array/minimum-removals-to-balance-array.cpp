class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int maxLen = 1;  // at least one element is always balanced
        int l = 0;

        for (int r = 0; r < n; r++) {
            while ((long long)nums[r] > (long long)k * nums[l]) {
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
        }

        return n - maxLen;
    }
};
