//
// Created by Haim Adrian on 25-Aug-19.
//

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

typedef int treeNodeType;

typedef struct node {
    treeNodeType data;
    struct node *left, *right, *parent;
} treeNode;

treeNode *createTree(treeNodeType value);
void freeTree(treeNode *node);

treeNode *leftTree(treeNode *node);
treeNode *rightTree(treeNode *node);
treeNode *parentTree(treeNode *node);
treeNode *rootTree(treeNode *node);
treeNodeType treeData(treeNode *node);

int setLeftTree(treeNode *root, treeNode *node);
int setRightTree(treeNode *root, treeNode *node);
treeNode * findTreeNode(treeNode *root, treeNodeType data);

int findPathToNode(treeNode *root, treeNode *node, treeNode ***path, int *length);

int isTreeEmpty(treeNode *tree);
int isLeaf(treeNode *tree);
unsigned int treeHeight(treeNode *tree);

void printTree(treeNode *root);
void printPreOrder(treeNode *root);
void printInOrder(treeNode *root);
void printPostOrder(treeNode *root);

#endif //BINTREE_BINTREE_H
