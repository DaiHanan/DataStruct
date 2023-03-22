#ifndef TLINKEDBTREE_H_INCLUDED
#define TLINKEDBTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现三叉链式二叉树
// 设计者：李钰林
// 版本号：2018-10-13

typedef struct _tLinkedBTreeNode{
    ElemType data;                      //存储数据
    struct _tLinkedBTreeNode* parent;   //双亲结点指针
    struct _tLinkedBTreeNode* left;     //左子树
    struct _tLinkedBTreeNode* right;    //右子树
}TLinkedBTreeNode, *TLinkedBTree;

//设该二叉树中只有正数，方便判断
//和二叉链式区别在创建和找结点

//初始化二叉树
Status TLinkedBTreeInit(TLinkedBTree* tree);
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status TLinkedBTreeCreateByNums(TLinkedBTree* tree, int nums[], int len);
//创建二叉树，采用（先序）数组   子函数
Status _TLinkedBTreeCreateByNums(TLinkedBTree* tree, int nums[], int len, int idx);
//创建二叉树，动态创建
Status TLinkedBTreeCreate(TLinkedBTree* tree);
//创建二叉树，动态创建子函数
Status _TLinkedBTreeCreate(TLinkedBTree* tree);
//销毁二叉树
Status TLinkedBTreeDestroy(TLinkedBTree tree);
//先序遍历二叉树
Status TLinkedBTreePreTraverse(TLinkedBTree tree, Status (*visit)(int*));
//中序遍历二叉树
Status TLinkedBTreeInTraverse(TLinkedBTree tree, Status (*visit)(int*));
//后序遍历二叉树
Status TLinkedBTreePostTraverse(TLinkedBTree tree, Status (*visit)(int*));
//层次遍历二叉树
Status TLinkedBTreeLevelTraverse(TLinkedBTree tree, Status (*visit)(int*));
//返回二叉树长度（元素个数）
int TLinkedBTreeLength(const TLinkedBTree tree);
//返回二叉树深度
int TLinkedBTreeDepth(const TLinkedBTree tree);
//返回二叉树带权路径长度 （WPL = weighted path length）
int TLinkedBTreeWPL(const TLinkedBTree tree);
//返回二叉树带权路径长度子函数
int _TLinkedBTreeWPL(const TLinkedBTree tree, int dep);
//打印根到某个节点的路径
Status TLinkedBTreePath(const TLinkedBTree tree, int num);
//验证元素num是否在该树里，并返回该结点
Status TLinkedBTreeContain(const TLinkedBTree tree, int num, TLinkedBTree* node);
//简单打印函数
Status TLinkedBTreeVisit(int* num);


#endif // TLINKEDBTREE_H_INCLUDED
