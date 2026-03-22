class Solution {
public:
    void rotate90(vector<vector<int>>& mat) {
        int n = mat.size();

        vector<vector<int>> temp(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[j][n-1-i] = mat[i][j];
            }
        }

        mat = temp;
    }

    bool equal(vector<vector<int>>& a, vector<vector<int>>& b) {
        int n = a.size();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j] != b[i][j])
                    return false;

        return true;
    }

    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {

        for (int i = 0; i < 4; i++) {

            if (equal(mat, target))
                return true;

            rotate90(mat);
        }

        return false;
    }
};