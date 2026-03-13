class Solution {
public:
    long long blocks(long long T, long long t) {
        long long l = 0, r = 1e6;

        while (l <= r) {
            long long m = (l + r) / 2;

            long long need = t * m * (m + 1) / 2;

            if (need <= T)
                l = m + 1;
            else
                r = m - 1;
        }

        return r;
    }

    bool can(long long T, int H, vector<int>& w) {

        long long total = 0;

        for (long long t : w) {
            total += blocks(T, t);
            if (total >= H) return true;
        }

        return false;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {

        long long l = 0, r = 1e18;
        long long ans = r;

        while (l <= r) {
            long long m = (l + r) / 2;

            if (can(m, mountainHeight, workerTimes)) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        return ans;
    }
};