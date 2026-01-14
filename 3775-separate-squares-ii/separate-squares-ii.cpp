class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        struct Event {
            double y, x1, x2;
            int type; // +1 add, -1 remove
        };

        vector<Event> events;
        for (auto &s : squares) {
            double x = s[0], y = s[1], l = s[2];
            events.push_back({y, x, x + l, +1});
            events.push_back({y + l, x, x + l, -1});
        }

        sort(events.begin(), events.end(),
             [](auto &a, auto &b) { return a.y < b.y; });

        multiset<pair<double, double>> active;

        auto unionWidth = [&]() {
            if (active.empty()) return 0.0;
            vector<pair<double,double>> v(active.begin(), active.end());
            sort(v.begin(), v.end());

            double width = 0;
            double L = v[0].first, R = v[0].second;
            for (int i = 1; i < v.size(); i++) {
                if (v[i].first > R) {
                    width += R - L;
                    L = v[i].first;
                    R = v[i].second;
                } else {
                    R = max(R, v[i].second);
                }
            }
            return width + (R - L);
        };

        // ---------- PASS 1: total union area ----------
        double totalArea = 0.0;
        double prevY = events[0].y;

        for (int i = 0; i < events.size(); ) {
            double currY = events[i].y;
            double dy = currY - prevY;
            totalArea += unionWidth() * dy;

            while (i < events.size() && events[i].y == currY) {
                if (events[i].type == 1)
                    active.insert({events[i].x1, events[i].x2});
                else
                    active.erase(active.find({events[i].x1, events[i].x2}));
                i++;
            }
            prevY = currY;
        }

        double half = totalArea / 2.0;

        // ---------- PASS 2: find split ----------
        active.clear();
        prevY = events[0].y;
        double areaSoFar = 0.0;

        for (int i = 0; i < events.size(); ) {
            double currY = events[i].y;
            double dy = currY - prevY;
            double width = unionWidth();
            double areaAdd = width * dy;

            if (areaSoFar + areaAdd >= half) {
                return prevY + (half - areaSoFar) / width;
            }

            areaSoFar += areaAdd;

            while (i < events.size() && events[i].y == currY) {
                if (events[i].type == 1)
                    active.insert({events[i].x1, events[i].x2});
                else
                    active.erase(active.find({events[i].x1, events[i].x2}));
                i++;
            }
            prevY = currY;
        }

        return prevY;
    }
};
