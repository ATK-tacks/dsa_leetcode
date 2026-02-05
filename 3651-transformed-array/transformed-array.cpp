class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                result[i] = 0;
            } else {
                int landing = ((i + nums[i]) % n + n) % n;
                result[i] = nums[landing];
            }
        }

        return result;
    }
};


