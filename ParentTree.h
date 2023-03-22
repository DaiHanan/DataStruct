#ifndef PARENTTREE_H_INCLUDED
#define PARENTTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现双亲表示法树
// 设计者：李钰林
// 版本号：2018-10-16

#define MAXSIZE 100         //最大结点个数

typedef struct{
    ElemType data;          //存储数据
    int parent;             //双亲下标
}PTNode;

typedef struct{
    PTNode nodes[MAXSIZE];  //数据数组
    int r;                  //根结点下标
    int n;                  //结点个数
}PTree;

//创建树
Status ParentTreeCreate(PTree** tree);
//通过数组创建树，方便测试
Status ParentTreeCreateByNums(PTree** tree, int nums[][2], int size);
//销毁树
Status ParentTreeDestroy(PTree* tree);
//获得结点的深度，未找到返回0
int ParentTreeNodeDepth(const PTree* tree, ElemType num);
//求树的高度
int ParentTreeDepth(const PTree* tree);
//先根序遍历
Status ParentTreePreTraverse(const PTree* tree, Status (*visit)(ElemType*));
//先根序遍历子函数，parent双亲结点
Status _ParentTreePreTraverse(const PTree* tree, int parent, Status (*visit)(ElemType*));
//后根序遍历
Status ParentTreePostTraverse(const PTree* tree, Status (*visit)(ElemType*));
//后根序遍历子函数，parent双亲结点
Status _ParentTreePostTraverse(const PTree* tree, int parent, Status (*visit)(ElemType*));
//层次遍历
Status ParentTreeLevelTraverse(const PTree* tree, Status (*visit)(ElemType*));
//根到节点的路径
Status ParentTreePath(const PTree* tree, ElemType num);
//简单打印函数
Status ParentTreeVisit(ElemType* num);

#endif // PARENTTREE_H_INCLUDED
