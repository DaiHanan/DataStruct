#ifndef TSMATRIX_H_INCLUDED
#define TSMATRIX_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现三元组稀疏矩阵
// 设计者：李钰林
// 版本号：2018-10-06


#define MAXSIZE 100 //最多100个非零元

typedef struct _triple{
    int i, j;           //非零元的行下标和列下标
    ElemType e;
}Triple;

typedef struct _TSMatrix{
    Triple data[MAXSIZE];    //存储矩阵非零元三元组表
    int line, col, count;           //存储矩阵的行数，列数，非零元个数
}TSMatrix;

//初始化矩阵（创建矩阵）
Status TSMatrixInit(TSMatrix** M, int line, int col);
//销毁矩阵
Status TSMatrixDestroy(TSMatrix* M);
//复制矩阵（强制改变矩阵大小）
Status TSMatrixCopy(TSMatrix* M, const TSMatrix* src);
//赋值指定位置（下标）的元素
Status TSMatrixAssign(TSMatrix* M, ElemType e, int line, int col);
//取出指定位置（下标）的元素
Status TSMatrixValue(const TSMatrix* M, ElemType* e, int line, int col);
//简单打印矩阵
Status TSMatrixPrint(const TSMatrix* M);

#endif // TSMATRIX_H_INCLUDED
