#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "MyDefinition.h"
#include "LinkedBTree.h"
#include <math.h>

// 功　能：实现各种查找（顺序）
// 设计者：李钰林
// 版本号：2018-11-20

#define MAXSIZE 100 //数组最大长度
//二叉平衡树用
#define LH 1//左高
#define EH 0//等高
#define RH -1//右高
typedef struct AVLTree{
    ElemType data;
    int bf;
    struct AVLTree* left;
    struct AVLTree* right;
}AVLTreeNode, *AVLTree;

//返回下标，未找到返回-1
//顺序查找
int SearchSeq(ElemType nums[], int size, ElemType elem);
//折半查找 条件：升序数组
int SearchBise(ElemType nums[], int size, ElemType elem);

//次优查找树
//次优查找树查找，设元素的权值为元素大小
ElemType SearchSecondOptimalTree(ElemType nums[], int size, ElemType elem);
//次优查找树查找 子函数 创建次优二叉树
void _SearchSecondOptimalTree_create(LinkedBTree* tree, ElemType nums[], ElemType sw[], int left, int right);
//次优查找树查找 子函数 递归查找
void _SearchSecondOptimalTree_find(LinkedBTree tree, ElemType num, ElemType* p);

//二叉查找树
//创建
Status BinTreeCreate(LinkedBTree* tree);
//查找，找到了就用指针p返回
Status BinTreeFind(LinkedBTree tree, ElemType elem, LinkedBTree f, LinkedBTree* p);
//插入
Status BinTreeInsert(LinkedBTree* tree, ElemType elem);
//删除
Status BinTreeDelete(LinkedBTree* tree, ElemType elem);
//删除 子函数
Status _BinTreeDelete(LinkedBTree* tree);
//平均查找长度
float BinTreeASL(LinkedBTree tree);
//平均查找长度 子函数
int _BinTreeASL(LinkedBTree tree, int dep, int* count);

//二叉平衡树
//左旋
Status AVLTreeLRotate(AVLTree* p);
//右旋
Status AVLTreeRRotate(AVLTree* p);
//左平衡
Status AVLTreeLBalance(AVLTree* p);
//右平衡
Status AVLTreeRBalance(AVLTree* p);
//插入
Status AVLTreeInsert(AVLTree* p, ElemType elem, Status* taller);
//查找，找到用指针p返回
Status AVLTreeFind(AVLTree t, ElemType elem, AVLTree* p);

/*
    B树，B+树.....
*/




//打印
Status SearchPrint(ElemType nums[], int size);

#endif // SEARCH_H_INCLUDED
