#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现各种排序（顺序）
// 设计者：李钰林
// 版本号：2018-11-20

#define MAXSIZE 100 //数组最大长度
#include <limits.h>

//直接插入排序
Status SortDirectInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//折半插入排序

Status SortBinaryInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));
//冒泡排序
Status SortBubb(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//快速排序
Status SortQuike(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));
//快速排序子函数1,简化主函数
void _SortQuike1(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b));
//快速排序子函数2,划分函数
int _SortQuike2(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b));

//选择排序
Status SortSelection(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//堆排序
Status SortHeap(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));
//堆排序子函数 从下标idx向下进行堆调整
void _SortHeap(ElemType nums[], int idx, int size, int (*order)(ElemType a, ElemType b));

//归并排序 非递归
Status SortMerge1(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));
//归并排序 递归
Status SortMerge2(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));
//归并排序 递归子函数
void _SortMerge2(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b));
//归并排序 子函数 合并两个已排好序的子数组
Status _SortMerge(ElemType nums[], int left, int mid, int right, int (*order)(ElemType a, ElemType b));

//希尔排序
Status SortShell(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//表排序
ElemType* SortTable(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//表插入排序
Status SortTableInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b));

//计数排序
Status SortCount(int nums[], int size);

//基数排序
Status SortRadix(int nums[], int size);
//基数排序 子函数 按照第d位进行计数排序
void _SortRadix1(int nums[], int size, int d);
//基数排序 子函数 获取传入元素第d位的数
int _SortRadix2(int num, int d);


//升序 返回1说明前者更大，否则返回0
int SortAscendOrder(ElemType a, ElemType b);
//打印
void SortPrint(ElemType nums[], int size);
//交换
void _Swap(ElemType nums[], int i, int j);

#endif // SORT_H_INCLUDED
