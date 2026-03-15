class Fancy {
public:
    const long long MOD = 1e9 + 7;

    vector<long long> arr;

    long long mul = 1;
    long long add = 0;

    long long modexp(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    long long inv(long long x) {
        return modexp(x, MOD - 2);
    }

    Fancy() {}

    void append(int val) {
        long long v = (val - add) % MOD;
        if (v < 0) v += MOD;
        v = v * inv(mul) % MOD;
        arr.push_back(v);
    }

    void addAll(int inc) {
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        mul = mul * m % MOD;
        add = add * m % MOD;
    }

    int getIndex(int idx) {
        if (idx >= arr.size()) return -1;
        return (arr[idx] * mul + add) % MOD;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */