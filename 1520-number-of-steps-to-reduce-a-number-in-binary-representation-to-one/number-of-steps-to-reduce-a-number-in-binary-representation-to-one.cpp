class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        int carry = 0;

        // traverse from right to left, ignore MSB
        for (int i = s.size() - 1; i > 0; i--) {
            int bit = (s[i] - '0') + carry;

            if (bit == 1) {
                // odd → add 1 then divide
                steps += 2;
                carry = 1;
            } else {
                // even → divide only
                steps += 1;
                // carry unchanged
            }
        }

        // handle final carry at MSB
        return steps + carry;
    }
};