class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size();
        int m = mat[0].size();

        // Prefix sum
        vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pref[i][j] = mat[i-1][j-1]
                           + pref[i-1][j]
                           + pref[i][j-1]
                           - pref[i-1][j-1];
            }
        }

        int lo = 0, hi = min(n, m), ans = 0;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            bool ok = false;

            for (int i = 0; i + mid <= n && !ok; i++) {
                for (int j = 0; j + mid <= m; j++) {
                    int sum = pref[i + mid][j + mid]
                            - pref[i][j + mid]
                            - pref[i + mid][j]
                            + pref[i][j];

                    if (sum <= threshold) {
                        ok = true;
                        break;
                    }
                }
            }

            if (ok) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};
