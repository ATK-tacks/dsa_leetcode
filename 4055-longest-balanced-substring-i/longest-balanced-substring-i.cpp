class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {

            vector<int> freq(26, 0);
            int distinct = 0;
            int maxFreq = 0;

            for (int r = l; r < n; r++) {

                int c = s[r] - 'a';

                if (freq[c] == 0) distinct++;

                freq[c]++;
                maxFreq = max(maxFreq, freq[c]);

                int len = r - l + 1;

                if (len % distinct == 0 &&
                    maxFreq * distinct == len) {

                    ans = max(ans, len);
                }
            }
        }

        return ans;
    }
};
