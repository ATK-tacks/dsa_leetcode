class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            unordered_set<int> even, odd;

            for (int r = l; r < n; r++) {
                if (nums[r] % 2 == 0)
                    even.insert(nums[r]);
                else
                    odd.insert(nums[r]);

                if (even.size() == odd.size()) {
                    ans = max(ans, r - l + 1);
                }

                // 🔥 pruning: cannot recover balance
                if (abs((int)even.size() - (int)odd.size()) > (n - r))
                    break;
            }
        }
        return ans;
    }
};
