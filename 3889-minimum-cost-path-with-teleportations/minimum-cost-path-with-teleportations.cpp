class Solution {
public:
    long long minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int N = m * n;
        auto id = [&](int r, int c){ return r * n + c; };

        // Sort cells by value
        vector<int> cells(N);
        iota(cells.begin(), cells.end(), 0);
        sort(cells.begin(), cells.end(), [&](int a, int b){
            int ra = a / n, ca = a % n;
            int rb = b / n, cb = b % n;
            return grid[ra][ca] < grid[rb][cb];
        });

        const long long INF = (long long)4e18;
        vector<vector<long long>> dist(k + 1, vector<long long>(N, INF));
        dist[0][0] = 0;

        using T = tuple<long long,int,int>; // (dist, idx, usedTele)
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0, 0, 0});

        // DSU "next pointer" per teleport layer:
        // if a cell is already activated for tele layer, skip it.
        vector<vector<int>> parent(k + 1, vector<int>(N + 1));
        for(int t = 0; t <= k; t++)
            for(int i = 0; i <= N; i++)
                parent[t][i] = i;

        function<int(int,int)> findp = [&](int t, int x) -> int {
            if (parent[t][x] == x) return x;
            return parent[t][x] = findp(t, parent[t][x]);
        };

        // pointer per teleport layer: which cells (sorted by value) are currently allowed
        vector<int> ptr(k + 1, 0);

        while(!pq.empty()) {
            auto [d, u, t] = pq.top();
            pq.pop();
            if (d != dist[t][u]) continue;

            int r = u / n, c = u % n;
            if (u == id(m-1, n-1)) return d;

            // Normal moves
            if (c + 1 < n) {
                int v = id(r, c + 1);
                long long nd = d + grid[r][c + 1];
                if (nd < dist[t][v]) {
                    dist[t][v] = nd;
                    pq.push({nd, v, t});
                }
            }
            if (r + 1 < m) {
                int v = id(r + 1, c);
                long long nd = d + grid[r + 1][c];
                if (nd < dist[t][v]) {
                    dist[t][v] = nd;
                    pq.push({nd, v, t});
                }
            }

            // Teleport moves
            if (t < k) {
                int curVal = grid[r][c];

                // Activate all cells with value <= curVal for layer t+1
                while (ptr[t+1] < N) {
                    int idx = cells[ptr[t+1]];
                    int rr = idx / n, cc = idx % n;
                    if (grid[rr][cc] > curVal) break;

                    // If not processed yet in this layer, relax it with cost 0
                    int p = findp(t+1, ptr[t+1]);
                    if (p == ptr[t+1]) {
                        // This activation is available globally for tele layer
                        if (d < dist[t+1][idx]) {
                            dist[t+1][idx] = d;
                            pq.push({d, idx, t+1});
                        }
                        // mark as processed
                        parent[t+1][ptr[t+1]] = ptr[t+1] + 1;
                    }

                    ptr[t+1]++;
                }
            }
        }

        return -1;
    }
};
