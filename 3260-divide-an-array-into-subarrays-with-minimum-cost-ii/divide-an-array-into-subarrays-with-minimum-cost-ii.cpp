class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0;

        auto balance = [&]() {
            while ((int)low.size() > k - 1) {
                auto it = prev(low.end());
                sumLow -= *it;
                high.insert(*it);
                low.erase(it);
            }
            while ((int)low.size() < k - 1 && !high.empty()) {
                auto it = high.begin();
                sumLow += *it;
                low.insert(*it);
                high.erase(it);
            }
            if (!low.empty() && !high.empty() && *prev(low.end()) > *high.begin()) {
                int a = *prev(low.end());
                int b = *high.begin();
                sumLow += b - a;
                low.erase(prev(low.end()));
                high.erase(high.begin());
                low.insert(b);
                high.insert(a);
            }
        };

        auto add = [&](int x) {
            if (low.empty() || x <= *prev(low.end())) {
                low.insert(x);
                sumLow += x;
            } else {
                high.insert(x);
            }
            balance();
        };

        auto remove = [&](int x) {
            auto itLow = low.find(x);
            if (itLow != low.end()) {
                sumLow -= x;
                low.erase(itLow);
            } else {
                auto itHigh = high.find(x);
                high.erase(itHigh);
            }
            balance();
        };

        long long ans = LLONG_MAX;

        // window indexes for candidates: [1 ... dist+1] first
        for (int i = 1; i <= dist + 1; i++)
            add(nums[i]);

        ans = min(ans, (long long)nums[0] + sumLow);

        for (int r = dist + 2; r < n; r++) {
            add(nums[r]);
            remove(nums[r - (dist + 1)]);
            ans = min(ans, (long long)nums[0] + sumLow);
        }

        return ans;
    }
};
