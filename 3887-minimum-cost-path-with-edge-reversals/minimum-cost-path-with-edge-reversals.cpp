class Solution {
public:
    long long minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(n);

        // Build transformed graph
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});        // normal edge
            adj[v].push_back({u, 2 * w});    // reversed using switch
        }

        const long long INF = 1e18;
        vector<long long> dist(n, INF);
        dist[0] = 0;

        priority_queue<pair<long long,int>,
            vector<pair<long long,int>>,
            greater<>> pq;

        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &[v, cost] : adj[u]) {
                if (dist[v] > d + cost) {
                    dist[v] = d + cost;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist[n-1] == INF ? -1 : dist[n-1];
    }
};
