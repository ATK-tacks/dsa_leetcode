class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, 
                                      vector<int>& healths, 
                                      string directions) {

        int n = positions.size();

        // {position, health, direction, original index}
        vector<tuple<int,int,char,int>> robots;

        for (int i = 0; i < n; i++) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }

        sort(robots.begin(), robots.end());

        vector<int> h(n);
        for (int i = 0; i < n; i++) {
            h[i] = get<1>(robots[i]);
        }

        stack<int> st; // indices of robots moving right

        for (int i = 0; i < n; i++) {

            if (get<2>(robots[i]) == 'R') {
                st.push(i);
            } 
            else {
                // current is 'L'
                while (!st.empty() && h[i] > 0) {

                    int j = st.top();

                    if (h[j] < h[i]) {
                        st.pop();
                        h[i]--;
                        h[j] = 0;
                    } 
                    else if (h[j] == h[i]) {
                        st.pop();
                        h[j] = 0;
                        h[i] = 0;
                        break;
                    } 
                    else {
                        h[j]--;
                        h[i] = 0;
                        break;
                    }
                }
            }
        }

        // collect survivors in original order
        vector<pair<int,int>> alive;

        for (int i = 0; i < n; i++) {
            if (h[i] > 0) {
                alive.push_back({get<3>(robots[i]), h[i]});
            }
        }

        sort(alive.begin(), alive.end());

        vector<int> res;
        for (auto &p : alive)
            res.push_back(p.second);

        return res;
    }
};