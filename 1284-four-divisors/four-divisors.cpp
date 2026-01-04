class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int sum = 0;
        int count,divsum;
        for(int val : nums){
          count = 0;
          divsum = 0;
            for(int j = 1;j*j<=val;j++){
                if((val%j)==0){
                    divsum += j;
                    count++;
                
                 int other = val/j;
                 if( other != j){
                 divsum += other;
                 count++;
                 }
                 if(count>4) break;
                }
            }
            if(count == 4){
            sum += divsum;
            }
            }
     return sum;
    }
};