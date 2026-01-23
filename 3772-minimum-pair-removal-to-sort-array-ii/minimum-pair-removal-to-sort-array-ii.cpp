class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();

        vector<long long> val(nums.begin(), nums.end());
        vector<int> left(n), right(n);
        vector<bool> alive(n, true);

        for (int i = 0; i < n; i++) {
            left[i] = i - 1;
            right[i] = i + 1;
        }

        // Count initial bad edges
        int bad = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (val[i] > val[i + 1]) bad++;
        }

        // Min heap of (sum, index)
        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<>
        > pq;

        for (int i = 0; i + 1 < n; i++) {
            pq.push({val[i] + val[i + 1], i});
        }

        int ops = 0;

        while (bad > 0) {
            auto [sum, i] = pq.top();
            pq.pop();

            int j = right[i];
            if (j >= n || !alive[i] || !alive[j]) continue;
            if (val[i] + val[j] != sum) continue;

            int L = left[i];
            int R = right[j];

            // Remove old bad edges
            if (L >= 0 && alive[L] && val[L] > val[i]) bad--;
            if (val[i] > val[j]) bad--;
            if (R < n && alive[R] && val[j] > val[R]) bad--;

            // Merge i and j
            val[i] = sum;
            alive[j] = false;

            right[i] = R;
            if (R < n) left[R] = i;

            // Add new bad edges
            if (L >= 0 && alive[L] && val[L] > val[i]) bad++;
            if (R < n && alive[R] && val[i] > val[R]) bad++;

            // Push updated adjacent pairs
            if (L >= 0) pq.push({val[L] + val[i], L});
            if (R < n) pq.push({val[i] + val[R], i});

            ops++;
        }

        return ops;
    }
};

