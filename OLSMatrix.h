#ifndef OLSMATRIX_H_INCLUDED
#define OLSMATRIX_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现十字链表矩阵
// 设计者：李钰林
// 版本号：2018-10-07

typedef struct _OLNode{
    int i, j;                       //非零元的行下标和列下标
    ElemType e;
    struct _OLNode* right, *down;   //非零元所在行列表的后续链域
}OLNode;

typedef struct _OLSMatrix{
    OLNode** rhead, ** chead;       //存储当前行、列中的第一个非零元指针域
    int line, col, count;           //存储矩阵的行数，列数，非零元个数
}OLSMatrix;

//初始化矩阵（创建矩阵）
Status OLSMatrixInit(OLSMatrix** M, int line, int col);
//销毁矩阵
Status OLSMatrixDestroy(OLSMatrix* M);
//复制矩阵（强制改变矩阵大小）
Status OLSMatrixCopy(OLSMatrix* M, const OLSMatrix* src);
//赋值指定位置（下标）的元素
Status OLSMatrixAssign(OLSMatrix* M, ElemType e, int line, int col);
//取出指定位置（下标）的元素
Status OLSMatrixValue(const OLSMatrix* M, ElemType* e, int line, int col);
//简单打印矩阵
Status OLSMatrixPrint(const OLSMatrix* M);

#endif // OLSMATRIX_H_INCLUDED
