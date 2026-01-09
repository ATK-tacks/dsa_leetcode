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
    void Traversal(TreeNode* root,vector<int>& ans){
        if(!root) return;
        Traversal(root->left,ans);
        Traversal(root->right,ans);
        ans.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        Traversal(root,ans);
        return ans;
    }
};
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;

        stack<pair<TreeNode*, bool>> st;
        st.push({root, false});

        while (!st.empty()) {
            auto [node, visited] = st.top();
            st.pop();

            if (!node) continue;

            if (!visited) {
                // Postorder: Left → Right → Node
                st.push({node, true});          // process later
                st.push({node->right, false}); // right child
                st.push({node->left, false});  // left child
            } else {
                ans.push_back(node->val);      // ROOT
            }
        }
        return ans;
    }
