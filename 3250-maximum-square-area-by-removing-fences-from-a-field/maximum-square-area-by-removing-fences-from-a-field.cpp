class Solution {
public:
    int maximizeSquareArea(int n, int m,
                           vector<int>& hFences,
                           vector<int>& vFences) {

        const long long MOD = 1e9 + 7;

        // Add boundaries
        hFences.push_back(1);
        hFences.push_back(n);
        vFences.push_back(1);
        vFences.push_back(m);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        unordered_set<long long> horizontalDistances;

        // All horizontal distances
        for (int i = 0; i < hFences.size(); i++) {
            for (int j = i + 1; j < hFences.size(); j++) {
                horizontalDistances.insert(
                    (long long)hFences[j] - hFences[i]
                );
            }
        }

        long long maxSide = 0;

        // Find maximum common distance
        for (int i = 0; i < vFences.size(); i++) {
            for (int j = i + 1; j < vFences.size(); j++) {
                long long d = (long long)vFences[j] - vFences[i];
                if (horizontalDistances.count(d)) {
                    maxSide = max(maxSide, d);
                }
            }
        }

        // ❗ No square possible
        if (maxSide == 0) return -1;

        return (maxSide * maxSide) % MOD;
    }
};
