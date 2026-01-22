class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int ops = 0;
        
        // Helper to check if array is non-decreasing
        auto sorted = [&](const vector<int>& arr) {
            for (int i = 0; i + 1 < arr.size(); i++) {
                if (arr[i] > arr[i+1]) return false;
            }
            return true;
        };
        
        while (!sorted(nums)) {
            int minSum = INT_MAX;
            int idx = -1;
            
            // Find leftmost adjacent pair with smallest sum
            for (int i = 0; i + 1 < nums.size(); i++) {
                int s = nums[i] + nums[i+1];
                if (s < minSum) {
                    minSum = s;
                    idx = i;
                }
            }
            
            // Merge the pair at idx
            nums[idx] = minSum;           // Replace left element
            nums.erase(nums.begin() + idx + 1);  // Remove right element
            ops++;
        }
        
        return ops;
    }
};
