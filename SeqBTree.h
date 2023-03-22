#ifndef SEQBTREE_H_INCLUDED
#define SEQBTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现顺序二叉树
// 设计者：李钰林
// 版本号：2018-10-13

#define MAXSIZE 100 //设二叉树最大容量为MAXSIZE（100）

typedef int SeqBTree[MAXSIZE];//设置为int类型是为了方便计算 带权路径长度

//设该二叉树中只有正数，方便判断

//初始化二叉树
Status SeqBTreeInit(SeqBTree tree);
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status SeqBTreeCreateByNums(SeqBTree tree, int nums[], int len);
//创建二叉树，动态创建
Status SeqBTreeCreate(SeqBTree tree);
//创建二叉树，动态创建子函数
Status _SeqBTreeCreate(SeqBTree tree, int idx);
//先序遍历二叉树
Status SeqBTreePreTraverse(SeqBTree tree, Status (*visit)(int*));
//先序遍历二叉树子函数
Status _SeqBTreePreTraverse(SeqBTree tree, Status (*visit)(int*), int idx);
//中序遍历二叉树
Status SeqBTreeInTraverse(SeqBTree tree, Status (*visit)(int*));
//中序遍历二叉树子函数
Status _SeqBTreeInTraverse(SeqBTree tree, Status (*visit)(int*), int idx);
//后序遍历二叉树
Status SeqBTreePostTraverse(SeqBTree tree, Status (*visit)(int*));
//后序遍历二叉树子函数
Status _SeqBTreePostTraverse(SeqBTree tree, Status (*visit)(int*), int idx);
//层次遍历二叉树
Status SeqBTreeLevelTraverse(SeqBTree tree, Status (*visit)(int*));
//返回二叉树长度（元素个数）
int SeqBTreeLength(const SeqBTree tree);
//返回二叉树深度
int SeqBTreeDepth(const SeqBTree tree);
//返回二叉树深度子函数
int _SeqBTreeDepth(const SeqBTree tree, int idx);
//返回二叉树带权路径长度 （WPL = weighted path length）
int SeqBTreeWPL(const SeqBTree tree);
//返回二叉树带权路径长度子函数
int _SeqBTreeWPL(const SeqBTree tree, int idx, int dep);
//打印根到某个节点的路径
Status SeqBTreePath(const SeqBTree tree, int num);
//验证元素num是否在该树里
Status SeqBTreeContain(const SeqBTree tree, int num);
//简单打印函数
Status SeqBTreeVisit(int* num);

#endif // SEQBTREE_H_INCLUDED
