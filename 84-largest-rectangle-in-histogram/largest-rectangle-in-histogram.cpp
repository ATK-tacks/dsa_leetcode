class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;          // stores indices
    int maxArea = 0;

    // Add a sentinel bar of height 0
    heights.push_back(0);

    for (int i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();

            int right = i;
            int left = st.empty() ? -1 : st.top();

            int width = right - left - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    return maxArea;
    }
};