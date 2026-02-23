class Solution {
public:
    bool hasAllCodes(string s, int k) {
        if (s.size() < k) return false;

        vector<bool> seen(1 << k, false);
        int mask = 0, count = 0;

        for (int i = 0; i < s.size(); i++) {
            mask = ((mask << 1) & ((1 << k) - 1)) | (s[i] - '0');

            if (i >= k - 1 && !seen[mask]) {
                seen[mask] = true;
                count++;
            }
        }

        return count == (1 << k);
    }
};