class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Prefix sums
        vector<vector<int>> row(n, vector<int>(m + 1, 0));
        vector<vector<int>> col(n + 1, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                row[i][j + 1] = row[i][j] + grid[i][j];
                col[i + 1][j] = col[i][j] + grid[i][j];
            }
        }

        // Try largest size first
        for (int k = min(n, m); k >= 2; k--) {
            for (int i = 0; i + k <= n; i++) {
                for (int j = 0; j + k <= m; j++) {

                    int target = row[i][j + k] - row[i][j];
                    bool ok = true;

                    // Check rows
                    for (int r = i; r < i + k && ok; r++) {
                        if (row[r][j + k] - row[r][j] != target)
                            ok = false;
                    }

                    // Check columns
                    for (int c = j; c < j + k && ok; c++) {
                        if (col[i + k][c] - col[i][c] != target)
                            ok = false;
                    }

                    // Main diagonal
                    int d1 = 0, d2 = 0;
                    for (int t = 0; t < k; t++) {
                        d1 += grid[i + t][j + t];
                        d2 += grid[i + t][j + k - 1 - t];
                    }

                    if (d1 != target || d2 != target)
                        ok = false;

                    if (ok) return k;
                }
            }
        }

        return 1;
    }
};
