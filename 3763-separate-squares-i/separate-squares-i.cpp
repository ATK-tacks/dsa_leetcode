class Solution {
 public:
  double separateSquares(vector<vector<int>>& squares) {
    // Compute half of the total area
    double halfArea = 0;
    for (auto &sq : squares) {
      long long l = sq[2];
      halfArea += (double)l * l;
    }
    halfArea /= 2.0;

    // Create events: (y, isStart, length)
    vector<tuple<int, bool, int>> events;
    events.reserve(squares.size() * 2);
    for (auto &sq : squares) {
      int y = sq[1];
      int l = sq[2];
      events.push_back({y, true, l});      // start of square
      events.push_back({y + l, false, l}); // end of square
    }

    // Sort by y
    sort(events.begin(), events.end(),
      [](auto &a, auto &b) { return get<0>(a) < get<0>(b); });

    double area = 0.0;
    long long width = 0;
    int prevY = get<0>(events[0]);

    for (auto &ev : events) {
      int y;
      bool isStart;
      int length;
      tie(y, isStart, length) = ev;

      // Compute area from prevY up to y
      double dy = (double)(y - prevY);
      double areaGain = width * dy;

      if (area + areaGain >= halfArea) {
        // If we reach half area in this strip, compute exact y
        return prevY + (halfArea - area) / (double)width;
      }

      area += areaGain;
      // Update current width (active vertical slice)
      width += (isStart ? length : -length);
      prevY = y;
    }

    // Should not normally reach here
    return (double)prevY;
  }
};
