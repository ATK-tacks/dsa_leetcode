
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int cost1 = 0, cost2 = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] != (i % 2 ? '1' : '0'))
                cost1++;

            if (s[i] != (i % 2 ? '0' : '1'))
                cost2++;
        }

        return min(cost1, cost2);
    }
};