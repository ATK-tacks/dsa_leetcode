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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);

        int level = 0;
        int bestLevel = 1;
        long long bestSum = LLONG_MIN;

        while (!q.empty()) {
            int sz = q.size();
            long long curSum = 0;
            level++;

            while (sz--) {
                auto node = q.front(); q.pop();
                curSum += node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            if (curSum > bestSum) {
                bestSum = curSum;
                bestLevel = level;
            }
        }

        return bestLevel;
    }
};
