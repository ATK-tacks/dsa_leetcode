class Solution {
public:
    string ans = "";
    int cnt = 0;

    void dfs(int n, int k, string &cur) {
        if (!ans.empty()) return;

        if (cur.size() == n) {
            cnt++;
            if (cnt == k) ans = cur;
            return;
        }

        for (char c : {'a', 'b', 'c'}) {
            if (!cur.empty() && cur.back() == c) continue;

            cur.push_back(c);
            dfs(n, k, cur);
            cur.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        string cur = "";
        dfs(n, k, cur);
        return ans;
    }
};