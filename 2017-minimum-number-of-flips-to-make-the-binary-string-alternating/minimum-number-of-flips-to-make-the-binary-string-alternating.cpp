class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        string t = s + s;

        int diff1 = 0, diff2 = 0;
        int ans = INT_MAX;

        for (int i = 0; i < t.size(); i++) {
            char c1 = (i % 2 ? '1' : '0');
            char c2 = (i % 2 ? '0' : '1');

            if (t[i] != c1) diff1++;
            if (t[i] != c2) diff2++;

            if (i >= n) {
                char pc1 = ((i - n) % 2 ? '1' : '0');
                char pc2 = ((i - n) % 2 ? '0' : '1');

                if (t[i - n] != pc1) diff1--;
                if (t[i - n] != pc2) diff2--;
            }

            if (i >= n - 1) {
                ans = min(ans, min(diff1, diff2));
            }
        }

        return ans;
    }
};