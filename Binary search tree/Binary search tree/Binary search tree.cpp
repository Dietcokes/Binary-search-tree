#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* bst_construct(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    struct TreeNode* node = newNode(postorder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd)
        return node;

    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == node->data)
            break;
    }

    node->right = bst_construct(inorder, postorder, inIndex + 1, inEnd, postIndex);
    node->left = bst_construct(inorder, postorder, inStart, inIndex - 1, postIndex);

    return node;
}

void bfs_traversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct TreeNode* current = queue[++front];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[++rear] = current->left;

        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

int main() {
    int inorder[] = { 5, 10, 15, 20, 25, 30, 45 };
    int postorder[] = { 5, 15, 10, 25, 45, 30, 20 };

    int n = sizeof(inorder) / sizeof(inorder[0]);
    int postIndex = n - 1;

    struct TreeNode* root = bst_construct(inorder, postorder, 0, n - 1, &postIndex);

    printf("BFS Traversal:\n");
    bfs_traversal(root);
    printf("\n");

    return 0;
}