#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const std::vector<int>& inorder, const std::vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) return nullptr;

    int rootValue = postorder[postEnd];
    TreeNode* root = new TreeNode(rootValue);

    int rootIndexInOrder = inStart;
    while (inorder[rootIndexInOrder] != rootValue) {
        ++rootIndexInOrder;
    }

    int leftSubtreeSize = rootIndexInOrder - inStart;

    root->left = buildTree(inorder, postorder, inStart, rootIndexInOrder - 1, postStart, postStart + leftSubtreeSize - 1);
    root->right = buildTree(inorder, postorder, rootIndexInOrder + 1, inEnd, postStart + leftSubtreeSize, postEnd - 1);

    return root;
}

std::vector<int> getRightSideView(const std::vector<int>& inorder, const std::vector<int>& postorder) {
    int n = inorder.size();
    if (n == 0) return {};

    TreeNode* root = buildTree(inorder, postorder, 0, n - 1, 0, n - 1);

    std::vector<int> result;
    std::queue<TreeNode*> levelNodes;
    levelNodes.push(root);

    while (!levelNodes.empty()) {
        int levelSize = levelNodes.size();
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = levelNodes.front();
            levelNodes.pop();

            if (i == levelSize - 1) {
                result.push_back(node->val); // Store the rightmost node's value at each level
            }

            if (node->left) levelNodes.push(node->left);
            if (node->right) levelNodes.push(node->right);
        }
    }

    delete root;
    return result;
}

int main() {
    std::vector<int> inorder, postorder;
    int temp;

    while (std::cin >> temp) {
        inorder.push_back(temp);
        if (std::cin.peek() == '\n') break;
    }

    while (std::cin >> temp) {
        postorder.push_back(temp);
        if (std::cin.peek() == '\n') break;
    }

    std::vector<int> result = getRightSideView(inorder, postorder);

    for (int val : result) {
        std::cout << val << std::endl;
    }

    return 0;
}