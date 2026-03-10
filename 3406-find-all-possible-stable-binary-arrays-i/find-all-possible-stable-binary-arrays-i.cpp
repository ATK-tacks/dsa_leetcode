class Solution {
public:
    static const int MOD = 1e9 + 7;

    int numberOfStableArrays(int zero, int one, int limit) {

        // dp[z][o][last][cnt]
        // last: 0 or 1
        // cnt: consecutive count

        vector dp(zero + 1,
            vector(one + 1,
                vector(2,
                    vector<int>(limit + 1, 0))));

        // start with 0
        if (zero > 0)
            dp[1][0][0][1] = 1;

        // start with 1
        if (one > 0)
            dp[0][1][1][1] = 1;

        for (int z = 0; z <= zero; z++) {
            for (int o = 0; o <= one; o++) {
                for (int last = 0; last < 2; last++) {
                    for (int cnt = 1; cnt <= limit; cnt++) {

                        int cur = dp[z][o][last][cnt];
                        if (!cur) continue;

                        // put 0
                        if (z < zero) {
                            if (last == 0) {
                                if (cnt < limit) {
                                    dp[z+1][o][0][cnt+1] =
                                        (dp[z+1][o][0][cnt+1] + cur) % MOD;
                                }
                            } else {
                                dp[z+1][o][0][1] =
                                    (dp[z+1][o][0][1] + cur) % MOD;
                            }
                        }

                        // put 1
                        if (o < one) {
                            if (last == 1) {
                                if (cnt < limit) {
                                    dp[z][o+1][1][cnt+1] =
                                        (dp[z][o+1][1][cnt+1] + cur) % MOD;
                                }
                            } else {
                                dp[z][o+1][1][1] =
                                    (dp[z][o+1][1][1] + cur) % MOD;
                            }
                        }
                    }
                }
            }
        }

        long long ans = 0;

        for (int last = 0; last < 2; last++)
            for (int cnt = 1; cnt <= limit; cnt++)
                ans = (ans + dp[zero][one][last][cnt]) % MOD;

        return ans;
    }
};