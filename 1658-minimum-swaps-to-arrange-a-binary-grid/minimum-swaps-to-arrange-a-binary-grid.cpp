class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> zeros(n);

        // Count trailing zeros for each row
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) {
                count++;
            }
            zeros[i] = count;
        }

        int swaps = 0;

        for (int i = 0; i < n; i++) {
            int required = n - 1 - i;
            int j = i;

            // Find suitable row
            while (j < n && zeros[j] < required) {
                j++;
            }

            if (j == n) return -1;

            // Bubble up
            while (j > i) {
                swap(zeros[j], zeros[j - 1]);
                swaps++;
                j--;
            }
        }

        return swaps;
    }
};