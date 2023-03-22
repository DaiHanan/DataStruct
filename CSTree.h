#ifndef CSTREE_H_INCLUDED
#define CSTREE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现孩子兄弟链表表示法树
// 设计者：李钰林
// 版本号：2018-11-6

typedef struct _CSNode{
    ElemType data;              //存储数据
    struct _CSNode* firstchild; //第一个孩子结点的指针
    struct _CSNode* nextsibling;//下一个兄弟结点的指针
}CSNode, *CSTree;

//创建树
Status CSTreeCreate(CSTree* tree);
//创建树子函数
Status _CSTreeCreate(CSTree* tree);
//通过（完全二叉树）数组创建树，方便测试
Status CSTreeCreateByNums(CSTree* tree, int nums[], int size);
//通过（完全二叉树）数组创建树，方便测试 子函数
Status _CSTreeCreateByNums(CSTree* tree, int nums[], int size, int idx);
//销毁树
Status CSTreeDestroy(CSTree tree);
//求树的高度
int CSTreeDepth(const CSTree tree);
//求树的长度
int CSTreeLength(const CSTree tree);
//先根序遍历
Status CSTreePreTraverse(const CSTree tree, Status (*visit)(ElemType*));
//后根序遍历
Status CSTreePostTraverse(const CSTree tree, Status (*visit)(ElemType*));
//层次遍历
Status CSTreeLevelTraverse(const CSTree tree, Status (*visit)(ElemType*));
//验证元素num是否在该树里
Status CSTreeContain(const CSTree tree, ElemType num);
//根到节点的路径
Status CSTreePath(const CSTree tree, ElemType num);
//简单打印函数
Status CSTreeVisit(ElemType* num);

#endif // CSTREE_H_INCLUDED
