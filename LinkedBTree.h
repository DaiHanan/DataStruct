#ifndef LINKEDBTREE_H_INCLUDED
#define LINKEDBTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现二叉链式二叉树
// 设计者：李钰林
// 版本号：2018-10-13

typedef struct _linkedBTreeNode{
    ElemType data;                  //存储数据
    struct _linkedBTreeNode* left;  //左子树
    struct _linkedBTreeNode* right; //右子树
}LinkedBTreeNode, *LinkedBTree;

//设该二叉树中只有正数，方便判断

//初始化二叉树
Status LinkedBTreeInit(LinkedBTree* tree);
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status LinkedBTreeCreateByNums(LinkedBTree* tree, int nums[], int len);
//创建二叉树，采用（先序）数组创建是为了Demo方便   子函数
Status _LinkedBTreeCreateByNums(LinkedBTree* tree, int nums[], int len, int idx);
//创建二叉树，动态创建
Status LinkedBTreeCreate(LinkedBTree* tree);
//创建二叉树，动态创建子函数
Status _LinkedBTreeCreate(LinkedBTree* tree);
//销毁二叉树
Status LinkedBTreeDestroy(LinkedBTree tree);
//先序遍历二叉树
Status LinkedBTreePreTraverse(LinkedBTree tree, Status (*visit)(ElemType*));
//中序遍历二叉树
Status LinkedBTreeInTraverse(LinkedBTree tree, Status (*visit)(ElemType*));
//后序遍历二叉树
Status LinkedBTreePostTraverse(LinkedBTree tree, Status (*visit)(ElemType*));
//层次遍历二叉树
Status LinkedBTreeLevelTraverse(LinkedBTree tree, Status (*visit)(ElemType*));
//返回二叉树长度（元素个数）
int LinkedBTreeLength(const LinkedBTree tree);
//返回二叉树叶节点个数
int LinkedBTreeLeafCount(const LinkedBTree tree);
//返回二叉树度为1的结点个数
int LinkedBTreeNode_1Count(const LinkedBTree tree);
//返回二叉树深度
int LinkedBTreeDepth(const LinkedBTree tree);
//返回二叉树带权路径长度 （WPL = weighted path length）
int LinkedBTreeWPL(const LinkedBTree tree);
//返回二叉树带权路径长度子函数
int _LinkedBTreeWPL(const LinkedBTree tree, int dep, int* wpl);
//打印根到某个节点的路径 非递归  可与 打印全部结点函数 互相替换
Status LinkedBTreePath(const LinkedBTree tree, ElemType num);
//打印根到所有叶子节点的路径 递归
Status LinkedBTreeAllPath(const LinkedBTree tree);
//打印根到所有叶子节点的路径 递归 子函数
void _LinkedBTreeAllPath(const LinkedBTree tree, ElemType path[], int len);
//验证元素num是否在该树里
Status LinkedBTreeContain(const LinkedBTree tree, ElemType num);
//简单打印函数
Status LinkedBTreeVisit(ElemType* num);
//获得元素num所在结点指针
LinkedBTreeNode* LinkedBTreeGetNode(const LinkedBTree tree, ElemType num);
//交换二叉树所有结点的左右结点
Status LinkedBTreeReverseNode(LinkedBTree tree);

#endif // LINKEDBTREE_H_INCLUDED
