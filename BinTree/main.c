//
// Created by Haim Adrian on 25-Aug-19.
//

#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "binsearchtree.h"

treeNode_s *searchTreeForExercises();
treeNode *treeForExercises();

void ex1();
int countTreeNodes(treeNode *tree);
int countLeaves(treeNode *tree);

void ex2();
int treeNodeDepth(treeNode *tree, treeNode *node);
int treeNodeDepthRec(treeNode *tree, treeNode *node);

void ex3();
treeNode * lowestCommonAncestor(treeNode *root, treeNode *node1, treeNode *node2);
treeNode_s * lowestCommonAncestorInBinSearchTree(treeNode_s *root, treeNode_s *node1, treeNode_s *node2);

void ex4();
int areTreesEqual(treeNode *root1, treeNode *root2);

int main() {
    treeNode *root = treeForExercises();
    treeNode_s *root_s = searchTreeForExercises();

    printf("Binary Tree:\n");
    printTree(root);

    printf("Binary Search Tree:\n");
    printTree_s(root_s);

    printf("Preorder:\n");
    printPreOrder(root);
    printf("Inorder:\n");
    printInOrder(root);
    printf("Postorder:\n");
    printPostOrder(root);

    ex1();
    ex2();
    ex3();
    ex4();

    freeTree(root);
    freeTree_s(root_s);

    return 0;
}

//////////////////// EX1 ////////////////////
void ex1() {
    treeNode *root = treeForExercises();

    printf("\n******************** Ex1: ********************\n");
    printf("Amount of nodes in tree: %d\n", countTreeNodes(root));
    printf("Amount of leaves in tree: %d\n", countLeaves(root));

    freeTree(root);
}

int countTreeNodes(treeNode *tree) {
    return isTreeEmpty(tree) ? 0 : 1 + countTreeNodes(leftTree(tree)) + countTreeNodes(rightTree(tree));
}

int countLeaves(treeNode *tree) {
    return isTreeEmpty(tree) ? 0 : isLeaf(tree) + countLeaves(leftTree(tree)) + countLeaves(rightTree(tree));
}

//////////////////// EX2 ////////////////////
void ex2() {
    treeNode *root = treeForExercises();
    treeNode *threeNode = findTreeNode(root, 3);
    treeNode *sevenNode = findTreeNode(root, 7);
    treeNode *nineNode = findTreeNode(root, 9);
    treeNode *nonExistingNode = createTree(100);

    printf("\n******************** Ex2: ********************\n");
    printf("Depth calculation using parent: (%d)=%d, (%d)=%d, (%d)=%d, (%d)=%d\n", treeData(threeNode), treeNodeDepth(root, threeNode),
           treeData(sevenNode), treeNodeDepth(root, sevenNode),
           treeData(nineNode), treeNodeDepth(root, nineNode),
           treeData(nonExistingNode), treeNodeDepth(root, nonExistingNode));
    printf("Depth calculation using recursion: (%d)=%d, (%d)=%d, (%d)=%d, (%d)=%d\n", treeData(threeNode), treeNodeDepthRec(root, threeNode),
           treeData(sevenNode), treeNodeDepthRec(root, sevenNode),
           treeData(nineNode), treeNodeDepthRec(root, nineNode),
           treeData(nonExistingNode), treeNodeDepthRec(root, nonExistingNode));

    freeTree(root);
}

int treeNodeDepth(treeNode *tree, treeNode *node) {
    int depth = 0;
    treeNode *nodeIter = node;

    while ((nodeIter != NULL) && (nodeIter != tree)) {
        depth++;
        nodeIter = parentTree(nodeIter);
    }

    return (nodeIter != tree) ? -1 : depth;
}

int treeNodeDepthRec(treeNode *tree, treeNode *node) {
    int depth = -1, leftDepth, rightDepth;

    if (!isTreeEmpty(tree)) {
        if (tree == node) {
            depth = 0;
        } else {
            leftDepth = treeNodeDepthRec(leftTree(tree), node);
            rightDepth = treeNodeDepthRec(rightTree(tree), node);

            if (leftDepth >= 0) {
                depth = leftDepth + 1;
            } else if (rightDepth >= 0) {
                depth = rightDepth + 1;
            }
        }
    }

    return depth;
}

//////////////////// EX3 ////////////////////
void ex3() {
    treeNode *root = treeForExercises();
    treeNode *threeNode = findTreeNode(root, 3);
    treeNode *sevenNode = findTreeNode(root, 7);
    treeNode *tenNode = findTreeNode(root, 10);
    treeNode *firstCommonAncestor, *secondCommonAncestor;

    treeNode_s *root_s = searchTreeForExercises();
    treeNode_s *threeNode_s = findTreeNode_s(root_s, 3);
    treeNode_s *sevenNode_s = findTreeNode_s(root_s, 7);
    treeNode_s *sixNode_s = findTreeNode_s(root_s, 6);
    treeNode_s *nineNode_s = findTreeNode_s(root_s, 9);
    treeNode_s *firstCommonAncestor_s, *secondCommonAncestor_s;

    printf("\n******************** Ex3: ********************\n");
    printf("BinTree:\n");
    firstCommonAncestor = lowestCommonAncestor(root, threeNode, sevenNode);
    secondCommonAncestor = lowestCommonAncestor(root, threeNode, tenNode);
    printf("\nLCA of %d and %d is: %d\n", treeData(threeNode), treeData(sevenNode), treeData(firstCommonAncestor));
    printf("LCA of %d and %d is: %d\n", treeData(threeNode), treeData(tenNode), treeData(secondCommonAncestor));

    printf("\nBinSearchTree:\n");
    firstCommonAncestor_s = lowestCommonAncestorInBinSearchTree(root_s, threeNode_s, sevenNode_s);
    secondCommonAncestor_s = lowestCommonAncestorInBinSearchTree(root_s, sixNode_s, nineNode_s);
    printf("LCA of %d and %d is: %d\n", treeData_s(threeNode_s), treeData_s(sevenNode_s), treeData_s(firstCommonAncestor_s));
    printf("LCA of %d and %d is: %d\n", treeData_s(sixNode_s), treeData_s(nineNode_s), treeData_s(secondCommonAncestor_s));

    freeTree(root);
    freeTree_s(root_s);
}

void printPath(treeNode **path, int length) {
    int i;

    printf("Path from root to node: %d", treeData(path[0]));
    for (i = 1; i < length; i++) {
        printf("->%d", treeData(path[i]));
    }
    printf("\n");
}

treeNode * lowestCommonAncestor(treeNode *root, treeNode *node1, treeNode *node2) {
    treeNode *ancestor = NULL, **path1, **path2;
    int path1Length, path2Length, i;

    findPathToNode(root, node1, &path1, &path1Length);
    findPathToNode(root, node2, &path2, &path2Length);

    printPath(path1, path1Length);
    printPath(path2, path2Length);

    // Once we find different nodes in the paths, it means the LCA is one before them.
    for (i = 0; (i < path1Length) && (i < path2Length) && (!ancestor); i++) {
        if (path1[i] != path2[i]) {
            ancestor = path1[i-1];
        }
    }

    free(path1);
    free(path2);

    return ancestor;
}

treeNode_s * lowestCommonAncestorInBinSearchTree(treeNode_s *root, treeNode_s *node1, treeNode_s *node2) {
    treeNode_s *ancestor = NULL;
    treeNodeType_s currData, n1Data, n2Data;

    if (root) {
        currData = treeData_s(root);
        n1Data = treeData_s(node1);
        n2Data = treeData_s(node2);

        if ((currData > n1Data) && (currData > n2Data)) {
            // When current node is bigger than both nodes, it means the LCA is on the left sub tree.
            ancestor = lowestCommonAncestorInBinSearchTree(root->left, node1, node2);
        } else if ((currData < n1Data) && (currData < n2Data)) {
            // When current node is lower than both nodes, it means the LCA is on the right sub tree.
            ancestor = lowestCommonAncestorInBinSearchTree(root->right, node1, node2);
        } else {
            // Current node is between node1 and node2, so this is the LCA.
            ancestor = root;
        }
    }

    return ancestor;
}

//////////////////// EX4 ////////////////////
void ex4() {
    treeNode *root = treeForExercises();
    treeNode *root2 = treeForExercises();

    printf("\n******************** Ex4: ********************\n");
    printf("Tree equals to itself? %s\n", areTreesEqual(root, root) ? "Yes" : "No");
    printf("Trees equal before change? %s\n", areTreesEqual(root, root2) ? "Yes" : "No");

    setLeftTree(root2, createTree(10));
    printf("Trees equal after change? %s\n", areTreesEqual(root, root2) ? "Yes" : "No");

    freeTree(root);
    freeTree(root2);
}

int areTreesEqual(treeNode *root1, treeNode *root2) {
    if ((root1 == NULL) && (root2 == NULL)) {
        return 1;
    }

    return ((root1 != NULL) && (root2 != NULL) && (treeData(root1) == treeData(root2)) && areTreesEqual(leftTree(root1), leftTree(root2)) && areTreesEqual(rightTree(root1), rightTree(root2)));
}


//////////////////// COMMON ////////////////////
treeNode *treeForExercises() {
    treeNode *root, *son1, *son2, *grandson1, *grandson2, *grandson3, *grandson4, *greatgrandson1, *greatgrandson2, *greatgrandson3, *greatgrandson4, *greatgrandson5;
    int i = 1;

    root = createTree(i++);
    son1 = createTree(i++);
    grandson1 = createTree(i++);
    greatgrandson1 = createTree(i++);
    greatgrandson2 = createTree(i++);
    grandson2 = createTree(i++);
    greatgrandson3 = createTree(i++);
    son2 = createTree(i++);
    grandson3 = createTree(i++);
    greatgrandson4 = createTree(i++);
    greatgrandson5 = createTree(i++);
    grandson4 = createTree(i);

    setLeftTree(root, son1);
    setRightTree(root, son2);

    setLeftTree(son1, grandson1);
    setRightTree(son1, grandson2);
    setLeftTree(son2, grandson3);
    setRightTree(son2, grandson4);

    setLeftTree(grandson1, greatgrandson1);
    setRightTree(grandson1, greatgrandson2);
    setLeftTree(grandson2, greatgrandson3);
    setLeftTree(grandson3, greatgrandson4);
    setRightTree(grandson3, greatgrandson5);

    return root;
}

treeNode_s *searchTreeForExercises() {
    treeNode_s *root;

    root = createTree_s(5);
    insertTreeNode_s(root, createTree_s(3));
    insertTreeNode_s(root, createTree_s(2));
    insertTreeNode_s(root, createTree_s(4));
    insertTreeNode_s(root, createTree_s(7));
    insertTreeNode_s(root, createTree_s(6));
    insertTreeNode_s(root, createTree_s(8));
    insertTreeNode_s(root, createTree_s(1));
    insertTreeNode_s(root, createTree_s(9));

    return root;
}
