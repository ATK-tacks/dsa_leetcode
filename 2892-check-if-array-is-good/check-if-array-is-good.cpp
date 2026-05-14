class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size();

        int maxEl = n-1;

        int maxElCount = 0;

        for(int num : nums) {
            int val = abs(num);

            if(val > maxEl) {
                return false;
            } else if(val == maxEl) {
                maxElCount++;
            }

            if(nums[val] < 0) {
                if(val != maxEl) {
                    return false;
                } else if(maxElCount > 2) {
                    return false;
                }
            } else {
                nums[val] *= -1;
            }
        }

        return true;
    }
};