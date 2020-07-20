//
// Created by Haim Adrian
//

#ifndef BINTREE_BINSEARCHTREE_H
#define BINTREE_BINSEARCHTREE_H

typedef int treeNodeType_s;

typedef struct node_s {
    treeNodeType_s data;
    struct node_s *left, *right, *parent;
} treeNode_s;

treeNode_s *createTree_s(treeNodeType_s value);
void freeTree_s(treeNode_s *node);

treeNode_s *leftTree_s(treeNode_s *node);
treeNode_s *rightTree_s(treeNode_s *node);
treeNode_s *parentTree_s(treeNode_s *node);
treeNodeType_s treeData_s(treeNode_s *node);

int insertTreeNode_s(treeNode_s *root, treeNode_s *node);
treeNode_s * findTreeNode_s(treeNode_s *root, treeNodeType_s data);

int isTreeEmpty_s(treeNode_s *tree);
int isLeaf_s(treeNode_s *tree);
unsigned int treeHeight_s(treeNode_s *tree);

void printTree_s(treeNode_s *root);
void printPreOrder_s(treeNode_s *root);
void printInOrder_s(treeNode_s *root);
void printPostOrder_s(treeNode_s *root);

#endif //BINTREE_BINSEARCHTREE_H
