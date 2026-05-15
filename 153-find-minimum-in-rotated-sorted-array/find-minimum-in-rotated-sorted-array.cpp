class Solution {
public:
    int findMin(vector<int>& nums) {
        int st = 0;
        int end = nums.size()-1;
        int mid = st + (end-st)/2;
        int ans = INT_MAX;
        while(st<=end){
            if(nums[mid]>=nums[0]){
                st = mid + 1;
                ans = min(ans, nums[0]);
            }
            else{
                end = mid-1;
                ans = min(ans, nums[mid]);
            }
            mid = st + (end-st)/2;
        }
        return ans;
    }
};