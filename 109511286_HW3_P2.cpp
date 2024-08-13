#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;

    int rootValue = preorder[preStart];
    TreeNode* root = new TreeNode(rootValue);

    int rootIndexInOrder = inStart;
    while (rootIndexInOrder <= inEnd && inorder[rootIndexInOrder] != rootValue) {
        ++rootIndexInOrder;
    }

    int leftSubtreeSize = rootIndexInOrder - inStart;

    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSubtreeSize, inStart, rootIndexInOrder - 1);
    root->right = buildTree(preorder, inorder, preStart + leftSubtreeSize + 1, preEnd, rootIndexInOrder + 1, inEnd);

    return root;
}

void postorderTraversal(TreeNode* root, std::vector<int>& result) {
    if (!root) return;

    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.emplace_back(root->val);
}

std::vector<int> getPostOrderTraversal(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    int n = inorder.size();

    TreeNode* root = buildTree(preorder, inorder, 0, n - 1, 0, n - 1);

    std::vector<int> result;
    result.reserve(n);  // Reserve space for better performance
    postorderTraversal(root, result);
    return result;
}

int main() {
    std::vector<int> preorder, inorder;

    int temp;
    while (std::cin >> temp) {
        preorder.emplace_back(temp);
        if (std::cin.peek() == '\n') break;
    }

    while (std::cin >> temp) {
        inorder.emplace_back(temp);
        if (std::cin.peek() == '\n') break;
    }

    std::vector<int> result = getPostOrderTraversal(preorder, inorder);

    for (int val : result) {
        std::cout << val << std::endl;
    }

    return 0;
}