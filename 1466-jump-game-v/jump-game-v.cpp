class Solution {
public:
    int n;
    vector<int> t;

    int solve(vector<int>& arr, int d, int i) {
        if (t[i] != -1)
            return t[i];

        int result = 1; // count current index also

        // move left
        for (int j = i - 1; j >= max(0, i - d); j--) {
            // can't jump further once taller/equal element appears
            if (arr[j] >= arr[i])
                break;
            result = max(result, 1 + solve(arr, d, j));
        }

        // move right
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {
            // can't jump further once taller/equal element appears
            if (arr[j] >= arr[i])
                break;
            result = max(result, 1 + solve(arr, d, j));
        }

        return t[i] = result;
    }

    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        t.resize(n, -1);

        int maxJump = 1;
        // We need to try from every index
        for (int i = 0; i < n; i++) {
            maxJump = max(maxJump, solve(arr, d, i));
        }

        return maxJump;
    }
};