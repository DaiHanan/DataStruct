#ifndef THREADBTREE_H_INCLUDED
#define THREADBTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现线索二叉树
// 设计者：李钰林
// 版本号：2018-10-14

typedef enum{
    Link,       //指针
    Thread      //线索
}PointerTag;

typedef struct _threadBTreeNode{
    ElemType data;                     //存储数据
    PointerTag lTag;                   //左标志
    PointerTag rTag;                   //右标志
    struct _threadBTreeNode* left;     //左子树
    struct _threadBTreeNode* right;    //右子树
}ThreadBTreeNode, *ThreadBTree;

//设该二叉树中只有正数，方便判断

//初始化二叉树
Status ThreadBTreeInit(ThreadBTree* tree);
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status ThreadBTreeCreateByNums(ThreadBTree* tree, int nums[], int len);
//创建二叉树，采用（先序）数组   子函数
Status _ThreadBTreeCreateByNums(ThreadBTree* tree, int nums[], int len, int idx);
//创建二叉树，动态创建
Status ThreadBTreeCreate(ThreadBTree* tree);
//创建二叉树，动态创建子函数
Status _ThreadBTreeCreate(ThreadBTree* tree);
//销毁二叉树
Status ThreadBTreeDestroy(ThreadBTree tree);
//线索化二叉树（中序）
Status ThreadBTreeInThreading(ThreadBTree* head, ThreadBTree tree);
//线索化二叉树（中序）子函数， pre存当前结点的前一个结点
Status _ThreadBTreeInThreading(ThreadBTree tree, ThreadBTree* pre);
//遍历二叉树（中序）
Status ThreadBTreeInTraverse(ThreadBTree head, Status (*visit)(int*));
//简单打印函数
Status ThreadBTreeVisit(int* num);

#endif // THREADBTREE_H_INCLUDED
