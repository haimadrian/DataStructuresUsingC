//
// Created by Haim Adrian on 25-Aug-19.
//

#include <stdio.h>
#include <stdlib.h>
#include "consoleutils.h"
#include "bintree.h"
#include "stack.h"

#define TRUE 1
#define FALSE 0
#define SPACE 2

treeNode *createTree(treeNodeType value) {
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    node->left = node->right = node->parent = NULL;
    node->data = value;
    return node;
}

void freeTree(treeNode *node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

treeNode *leftTree(treeNode *node) {
    return ((node == NULL) ? NULL : node->left);
}

treeNode *rightTree(treeNode *node) {
    return ((node == NULL) ? NULL : node->right);
}

treeNode *parentTree(treeNode *node) {
    return ((node == NULL) ? NULL : node->parent);
}

treeNode *rootTree(treeNode *node) {
    treeNode *root = NULL;

    while (node != NULL) {
        root = node;
        node = node->parent;
    }

    return root;
}

treeNodeType treeData(treeNode *node) {
    return isTreeEmpty(node) ? 0 : node->data;
}

int setLeftTree(treeNode *root, treeNode *node) {
    int success = FALSE;

    if (root) {
        success = TRUE;
        if (root->left) {
            freeTree(root->left);
        }

        root->left = node;
        node->parent = root;
    }

    return success;
}

int setRightTree(treeNode *root, treeNode *node) {
    int success = FALSE;

    if (root) {
        success = TRUE;
        if (root->right) {
            freeTree(root->right);
        }

        root->right = node;
        node->parent = root;
    }

    return success;
}

treeNode * findTreeNode(treeNode *root, treeNodeType data) {
    treeNode * node = NULL;

    if (root) {
        if (root->data == data) {
            node = root;
        } else {
            node = findTreeNode(root->left, data);
            if (!node) {
                node = findTreeNode(root->right, data);
            }
        }
    }

    return node;
}

int findPathToNode(treeNode *root, treeNode *node, treeNode ***path, int *length) {
    int found = FALSE;
    treeNode *iter = node;
    stack st;
    stackType item;

    if (path) {
        createStack(&st);

        while (iter != NULL) {
            push(&st, iter);
            if (iter->data == root->data) {
                found = TRUE;
                break;
            }

            iter = parentTree(iter);
        }

        if (found) {
            *length = 0;
            (*path) = malloc((stackSize(&st)) * sizeof(treeNode *));
            while (!isStackEmpty(&st)) {
                pop(&st, &item);
                (*path)[(*length)++] = item;
            }
        }

        freeStack(&st);
    }

    return found;
}

int isTreeEmpty(treeNode *tree) {
    return (tree == NULL);
}

int isLeaf(treeNode *tree) {
    return ((tree == NULL) ? FALSE : ((tree->left == NULL) && (tree->right == NULL)));
}

unsigned int treeHeight(treeNode *tree) {
    unsigned int height = 0;

    if ((tree) && (!isLeaf(tree))) {
        height = max(treeHeight(tree->left), treeHeight(tree->right)) + 1;
    }

    return height;
}

void printTreeUtil(treeNode *node, int *x, int y) {
    if (node != NULL) {
        printTreeUtil(node->left, x, y + SPACE);
        gotoxy(*x, y);
        printf("%d", node->data);
        *x += SPACE;
        printTreeUtil(node->right, x, y + SPACE);
    }
}

void printTree(treeNode *root) {
    int x = 0, y = GetConsoleCursorPosition().Y;
    printTreeUtil(root, &x, y);
    gotoxy(50, ((int)treeHeight(root) * SPACE) + y);
    printf("\n\n");
}

void printPreOrderUtil(treeNode *root) {
    if (root) {
        printf("%d ", root->data);
        printPreOrderUtil(root->left);
        printPreOrderUtil(root->right);
    }
}

void printPreOrder(treeNode *root) {
    if (root) {
        printPreOrderUtil(root);
        printf("\n");
    }
}

void printInOrderUtil(treeNode *root) {
    if (root) {
        printInOrderUtil(root->left);
        printf("%d ", root->data);
        printInOrderUtil(root->right);
    }
}

void printInOrder(treeNode *root) {
    if (root) {
        printInOrderUtil(root);
        printf("\n");
    }
}

void printPostOrderUtil(treeNode *root) {
    if (root) {
        printPostOrderUtil(root->left);
        printPostOrderUtil(root->right);
        printf("%d ", root->data);
    }
}

void printPostOrder(treeNode *root) {
    if (root) {
        printPostOrderUtil(root);
        printf("\n");
    }
}
