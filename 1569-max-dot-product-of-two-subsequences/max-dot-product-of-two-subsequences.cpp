class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        const int NEG_INF = -1e9;

        vector<vector<int>> dp(n+1, vector<int>(m+1, NEG_INF));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int take = nums1[i-1] * nums2[j-1] + max(0, dp[i-1][j-1]);
                int skip1 = dp[i-1][j];
                int skip2 = dp[i][j-1];
                dp[i][j] = max({take, skip1, skip2});
            }
        }
        return dp[n][m];
    }
};
