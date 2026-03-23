class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        const long long MOD = 1e9 + 7;

        vector<vector<long long>> mx(m, vector<long long>(n));
        vector<vector<long long>> mn(m, vector<long long>(n));

        mx[0][0] = mn[0][0] = grid[0][0];

        // first column
        for (int i = 1; i < m; i++) {
            mx[i][0] = mn[i][0] = mx[i-1][0] * grid[i][0];
        }

        // first row
        for (int j = 1; j < n; j++) {
            mx[0][j] = mn[0][j] = mx[0][j-1] * grid[0][j];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                long long a = mx[i-1][j] * grid[i][j];
                long long b = mn[i-1][j] * grid[i][j];
                long long c = mx[i][j-1] * grid[i][j];
                long long d = mn[i][j-1] * grid[i][j];

                mx[i][j] = max({a, b, c, d});
                mn[i][j] = min({a, b, c, d});
            }
        }

        long long ans = mx[m-1][n-1];

        if (ans < 0) return -1;

        return ans % MOD;
    }
};