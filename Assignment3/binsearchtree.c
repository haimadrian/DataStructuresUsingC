//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "binsearchtree.h"

#ifdef _WIN32
#include "consoleutils.h"
#endif

#define TRUE 1
#define FALSE 0
#define SPACE 2

treeNode_s *createTree_s(treeNodeType_s value) {
    treeNode_s *node = (treeNode_s *)malloc(sizeof(treeNode_s));
    node->left = node->right = node->parent = NULL;
    node->data = value;
    return node;
}

void freeTree_s(treeNode_s *node) {
    if (node) {
        freeTree_s(node->left);
        freeTree_s(node->right);
        free(node);
    }
}

treeNode_s *leftTree_s(treeNode_s *node) {
    return ((node == NULL) ? NULL : node->left);
}

treeNode_s *rightTree_s(treeNode_s *node) {
    return ((node == NULL) ? NULL : node->right);
}

treeNode_s *parentTree_s(treeNode_s *node) {
    return ((node == NULL) ? NULL : node->parent);
}

treeNodeType_s treeData_s(treeNode_s *node) {
    return isTreeEmpty_s(node) ? 0 : node->data;
}

int insertTreeNode_s(treeNode_s *root, treeNode_s *node) {
    int success = FALSE;

    if (root) {
        if (root->data == node->data) {
            printf("Element %d already presents in tree.\n", node->data);
        } else if (root->data < node->data) {
            if (root->right) {
                success = insertTreeNode_s(root->right, node);
            } else {
                root->right = node;
                node->parent = root;
                success = TRUE;
            }
        } else if (root->left) {
            success = insertTreeNode_s(root->left, node);
        } else {
            root->left = node;
            node->parent = root;
            success = TRUE;
        }
    }

    return success;
}

treeNode_s * findTreeNode_s(treeNode_s *root, treeNodeType_s data) {
    treeNode_s * node = NULL;

    if (root) {
        if (root->data == data) {
            node = root;
        } else if (root->data < data) {
            if (root->right) {
                node = findTreeNode_s(root->right, data);
            }
        } else if (root->left) {
            node = findTreeNode_s(root->left, data);
        }
    }

    return node;
}

int isTreeEmpty_s(treeNode_s *tree) {
    return (tree == NULL);
}

int isLeaf_s(treeNode_s *tree) {
    return ((tree == NULL) ? FALSE : ((tree->left == NULL) && (tree->right == NULL)));
}

unsigned int treeHeight_s(treeNode_s *tree) {
    unsigned int height = 0;

    if ((tree) && (!isLeaf_s(tree))) {
        height = max(treeHeight_s(tree->left), treeHeight_s(tree->right)) + 1;
    }

    return height;
}

void printTreeUtil_s(treeNode_s *node, int *x, int y) {
#ifdef _WIN32
    if (node != NULL) {
        printTreeUtil_s(node->left, x, y + SPACE);
        gotoxy(*x, y);
        printf("%d", node->data);
        *x += SPACE;
        printTreeUtil_s(node->right, x, y + SPACE);
    }
#endif
}

void printTree_s(treeNode_s *root) {
#ifdef _WIN32
    int x = 0, y = GetConsoleCursorPosition().Y;
    printTreeUtil_s(root, &x, y);
    gotoxy(50, ((int)treeHeight_s(root) * SPACE) + y);
    printf("\n\n");
#else
    printf("printTree_s is not supported on non Windows systems. Sorry.\n");
#endif
}

void printPreOrderUtil_s(treeNode_s *root) {
    if (root) {
        printf("%d ", root->data);
        printPreOrderUtil_s(root->left);
        printPreOrderUtil_s(root->right);
    }
}

void printPreOrder_s(treeNode_s *root) {
    if (root) {
        printPreOrderUtil_s(root);
        printf("\n");
    }
}

void printInOrderUtil_s(treeNode_s *root) {
    if (root) {
        printInOrderUtil_s(root->left);
        printf("%d ", root->data);
        printInOrderUtil_s(root->right);
    }
}

void printInOrder_s(treeNode_s *root) {
    if (root) {
        printInOrderUtil_s(root);
        printf("\n");
    }
}

void printPostOrderUtil_s(treeNode_s *root) {
    if (root) {
        printPostOrderUtil_s(root->left);
        printPostOrderUtil_s(root->right);
        printf("%d ", root->data);
    }
}

void printPostOrder_s(treeNode_s *root) {
    if (root) {
        printPostOrderUtil_s(root);
        printf("\n");
    }
}
