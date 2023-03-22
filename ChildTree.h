#ifndef CHILDTREE_H_INCLUDED
#define CHILDTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现孩子链表表示法树
// 设计者：李钰林
// 版本号：2018-11-6   （最近事情有点多）

#define MAXSIZE 100         //最大结点个数

typedef struct _childNode{
    int child;              //孩子结点的下标
    struct _childNode* next;//指向下一个孩子结点的指针
}CNode;

typedef struct{
    ElemType data;          //存储数据
    CNode* first;           //第一个孩子结点的指针
}CTNode;

typedef struct{
    CTNode nodes[MAXSIZE];  //数据数组
    int r;                  //根结点下标
    int n;                  //结点个数
}CTree;

//创建树
Status ChildTreeCreate(CTree** tree);
//通过数组创建树，方便测试
Status ChildTreeCreateByNums(CTree** tree, int nums[][2], int size);
//销毁树
Status ChildTreeDestroy(CTree* tree);
//获得结点的深度，未找到返回0
int ChildTreeNodeDepth(const CTree* tree, ElemType num);
//求树的高度
int ChildTreeDepth(const CTree* tree);
//先根序遍历
Status ChildTreePreTraverse(const CTree* tree, Status (*visit)(ElemType*));
//先根序遍历子函数，index当前结点下标
Status _ChildTreePreTraverse(const CTree* tree, int index, Status (*visit)(ElemType*));
//后根序遍历
Status ChildTreePostTraverse(const CTree* tree, Status (*visit)(ElemType*));
//后根序遍历子函数，index当前结点下标
Status _ChildTreePostTraverse(const CTree* tree, int index, Status (*visit)(ElemType*));
//层次遍历
Status ChildTreeLevelTraverse(const CTree* tree, Status (*visit)(ElemType*));
//根到节点的路径
Status ChildTreePath(const CTree* tree, ElemType num);
//简单打印函数
Status ChildTreeVisit(ElemType* num);

#endif // CHILDTREE_H_INCLUDED
