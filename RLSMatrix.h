#ifndef RLSMATRIX_H_INCLUDED
#define RLSMATRIX_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现行逻辑链接稀疏矩阵
// 设计者：李钰林
// 版本号：2018-10-06

#define MAXSIZE 100 //最多100个非零元
#define MAXRC 50    //最多50行

typedef struct _rTriple{
    int i, j;           //非零元的行下标和列下标
    ElemType e;
}rTriple;

typedef struct _RLSMatrix{
    rTriple data[MAXSIZE];    //存储矩阵非零元三元组表
    int rIdx[MAXRC];     //存储矩阵各行第一个非零元的下标，若没有则为col
    int line, col, count;    //存储矩阵的行数，列数，非零元个数
}RLSMatrix;

//初始化矩阵（创建矩阵）
Status RLSMatrixInit(RLSMatrix** M, int line, int col);
//销毁矩阵
Status RLSMatrixDestroy(RLSMatrix* M);
//复制矩阵（强制改变矩阵大小）
Status RLSMatrixCopy(RLSMatrix* M, const RLSMatrix* src);
//赋值指定位置（下标）的元素
Status RLSMatrixAssign(RLSMatrix* M, ElemType e, int line, int col);
//取出指定位置（下标）的元素
Status RLSMatrixValue(const RLSMatrix* M, ElemType* e, int line, int col);
//简单打印矩阵
Status RLSMatrixPrint(const RLSMatrix* M);

//获得line行第一个非零元的下标，没有返回-1
Status RLSMatrixGetLineFirstElem(const RLSMatrix* M, int line,int* col);

#endif // RLSMATRIX_H_INCLUDED
