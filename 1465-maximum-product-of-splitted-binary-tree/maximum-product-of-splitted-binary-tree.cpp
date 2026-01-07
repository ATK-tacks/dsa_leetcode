/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    long long total = 0;
    long long ans = 0;
    const int MOD = 1e9+7;

    long long getSum(TreeNode* root){
        if(!root) return 0;
        return root->val + getSum(root->left) + getSum(root->right);
    }

    long long dfs(TreeNode* root){
        if(!root) return 0;

        long long s = root->val + dfs(root->left) + dfs(root->right);

        ans = max(ans, s * (total - s));
        return s;
    }

    int maxProduct(TreeNode* root) {
        total = getSum(root);
        dfs(root);
        return ans % MOD;
    }
};
