class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        long long sum = 0;
        int negcount = 0;
        long long mn = LLONG_MAX;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                if(matrix[i][j]<0) negcount++;
                    sum += llabs(matrix[i][j]);
                    mn = min(mn,llabs(matrix[i][j])); 
            }
        }
    if(negcount%2==0) return sum;
    return (sum-(2*mn));
    }
};