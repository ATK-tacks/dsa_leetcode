class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int first = nums[0];

        int mn1 = INT_MAX, mn2 = INT_MAX;
        for (int i = 1; i < nums.size(); i++) {
            int x = nums[i];
            if (x < mn1) {
                mn2 = mn1;
                mn1 = x;
            } else if (x < mn2) {
                mn2 = x;
            }
        }
        return first + mn1 + mn2;
    }
};
