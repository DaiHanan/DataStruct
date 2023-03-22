#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "MyDefinition.h"
#include <stdarg.h>

// 功　能：实现顺序矩阵
// 设计者：李钰林
// 版本号：2018-10-06

#define MAX_ARRAY_DIM 5 //假设最多五个维度

typedef struct _array{
    ElemType* base;     //数组元素首地址
    int dim;            //数组维数
    int* bounds;        //存储数组维数的数组首地址
    int* constants;     //存储数组元素权重的数组首地址
}Array;

//初始化数组（创建数组）
Status ArrayInit(Array** A, int dim, ...);
//销毁数组
Status ArrayDestroy(Array* A);
//复制数组（强制改变数组大小）
Status ArrayCopy(Array* A, const Array* src);

//定位元素位置（辅助函数）
Status ArrayLocate(const Array* A, va_list ap, int* off);
//赋值指定位置的元素
Status ArrayAssign(Array* A, ElemType e, ...);
//取出指定位置的元素
Status ArrayValue(const Array* A, ElemType* e, ...);

#endif // ARRAY_H_INCLUDED
