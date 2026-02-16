class Solution {
public:
    int reverseBits(int n) {
        uint32_t x = (uint32_t) n;   // interpret bits safely
        uint32_t res = 0;

        for (int i = 0; i < 32; i++) {
            res <<= 1;
            res |= (x & 1);
            x >>= 1;
        }

        return (int) res;  // cast back to int
    }
};
