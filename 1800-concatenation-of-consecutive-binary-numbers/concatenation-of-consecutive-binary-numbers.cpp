class Solution {
public:
    int concatenatedBinary(int n) {
        const int MOD = 1e9 + 7;
        long long result = 0;
        int bits = 0;

        for (int i = 1; i <= n; i++) {
            // increase bit length if power of 2
            if ((i & (i - 1)) == 0)
                bits++;

            result = ((result << bits) % MOD + i) % MOD;
        }

        return result;
    }
};