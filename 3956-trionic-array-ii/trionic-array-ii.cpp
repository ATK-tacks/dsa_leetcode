class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        const long long NEG = -(1LL<<62);

        vector<long long> inc(n, NEG), incDec(n, NEG), tri(n, NEG);

        for (int i = 1; i < n; i++) {
            // 1) strictly increasing part (len >= 2)
            if (nums[i-1] < nums[i]) {
                inc[i] = max(inc[i], (long long)nums[i-1] + nums[i]);
                if (inc[i-1] != NEG)
                    inc[i] = max(inc[i], inc[i-1] + nums[i]);
            }

            // 2) strictly decreasing part after increasing (len >= 2)
            if (nums[i-1] > nums[i]) {
                if (inc[i-1] != NEG)
                    incDec[i] = max(incDec[i], inc[i-1] + nums[i]);
                if (incDec[i-1] != NEG)
                    incDec[i] = max(incDec[i], incDec[i-1] + nums[i]);
            }

            // 3) strictly increasing part after incDec (len >= 2)
            if (nums[i-1] < nums[i]) {
                if (incDec[i-1] != NEG)
                    tri[i] = max(tri[i], incDec[i-1] + nums[i]);
                if (tri[i-1] != NEG)
                    tri[i] = max(tri[i], tri[i-1] + nums[i]);
            }
        }

        long long ans = NEG;
        for (int i = 0; i < n; i++) ans = max(ans, tri[i]);

        // guaranteed exists, so ans will be valid
        return ans;
    }
};
