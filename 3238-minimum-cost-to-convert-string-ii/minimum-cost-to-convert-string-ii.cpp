class Solution {
public:
    struct TrieNode {
        int nxt[26];
        int id;
        TrieNode() {
            for (int i = 0; i < 26; i++) nxt[i] = -1;
            id = -1;
        }
    };

    long long minimumCost(string source, string target,
                          vector<string>& original,
                          vector<string>& changed,
                          vector<int>& cost) {
        const long long INF = (long long)4e18;

        int n = (int)source.size();
        if ((int)target.size() != n) return -1;

        // ---- Step 1: compress unique strings ----
        unordered_map<string, int> mp;
        vector<string> all;

        auto getId = [&](const string& s) -> int {
            auto it = mp.find(s);
            if (it != mp.end()) return it->second;
            int id = (int)all.size();
            mp[s] = id;
            all.push_back(s);
            return id;
        };

        for (int i = 0; i < (int)original.size(); i++) {
            getId(original[i]);
            getId(changed[i]);
        }

        int V = (int)all.size();

        // ---- Step 2: build graph of conversions ----
        vector<vector<pair<int,int>>> g(V);
        for (int i = 0; i < (int)original.size(); i++) {
            int u = mp[original[i]];
            int v = mp[changed[i]];
            g[u].push_back({v, cost[i]});
        }

        // ---- Step 3: all-pairs shortest path via Dijkstra from each node ----
        vector<vector<long long>> dist(V, vector<long long>(V, INF));

        for (int s = 0; s < V; s++) {
            priority_queue<pair<long long,int>,
                           vector<pair<long long,int>>,
                           greater<pair<long long,int>>> pq;

            dist[s][s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[s][u]) continue;

                for (auto [v, w] : g[u]) {
                    if (dist[s][v] > d + w) {
                        dist[s][v] = d + w;
                        pq.push({dist[s][v], v});
                    }
                }
            }
        }

        // ---- Step 4: build trie containing ALL unique strings ----
        vector<TrieNode> trie;
        trie.emplace_back(); // root

        auto insertTrie = [&](const string& s, int id) {
            int node = 0;
            for (char ch : s) {
                int c = ch - 'a';
                if (trie[node].nxt[c] == -1) {
                    trie[node].nxt[c] = (int)trie.size();
                    trie.emplace_back();
                }
                node = trie[node].nxt[c];
            }
            trie[node].id = id;
        };

        for (int i = 0; i < V; i++) {
            insertTrie(all[i], i);
        }

        // ---- Step 5: DP over positions ----
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {
            // If characters already match, you can keep them without cost
            if (source[i] == target[i])
                dp[i] = min(dp[i], dp[i + 1]);

            int nodeS = 0, nodeT = 0;

            // try all substring lengths starting at i
            for (int j = i; j < n; j++) {
                int cs = source[j] - 'a';
                int ct = target[j] - 'a';

                if (nodeS != -1) nodeS = trie[nodeS].nxt[cs];
                if (nodeT != -1) nodeT = trie[nodeT].nxt[ct];

                if (nodeS == -1 || nodeT == -1) break;

                int idS = trie[nodeS].id;
                int idT = trie[nodeT].id;

                if (idS != -1 && idT != -1) {
                    long long cst = dist[idS][idT];
                    if (cst < INF && dp[j + 1] < INF) {
                        dp[i] = min(dp[i], cst + dp[j + 1]);
                    }
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
};