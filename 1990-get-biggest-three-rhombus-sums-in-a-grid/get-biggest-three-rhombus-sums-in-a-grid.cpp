class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        set<int> st;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // size = 0 (single cell)
                st.insert(grid[i][j]);

                for (int k = 1; ; k++) {

                    if (i + 2*k >= m) break;
                    if (j - k < 0 || j + k >= n) break;

                    int r = i;
                    int c = j;

                    int sum = 0;

                    // down-right
                    for (int t = 0; t < k; t++)
                        sum += grid[r+t][c+t];

                    // down-left
                    for (int t = 0; t < k; t++)
                        sum += grid[r+k+t][c+k-t];

                    // up-left
                    for (int t = 0; t < k; t++)
                        sum += grid[r+2*k-t][c-t];

                    // up-right
                    for (int t = 0; t < k; t++)
                        sum += grid[r+k-t][c-k+t];

                    st.insert(sum);
                }
            }
        }

        vector<int> res;

        auto it = st.rbegin();

        for (int i = 0; i < 3 && it != st.rend(); i++, it++)
            res.push_back(*it);

        return res;
    }
};