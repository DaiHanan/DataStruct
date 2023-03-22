#ifndef AHEAD_H_INCLUDED
#define AHEAD_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现顺序表
// 设计者：李钰林
// 版本号：2018-09-23

#define MAXSIZE 100 //假设只能装100个元素

typedef struct _seqList{
    ElemType* data;         //数组存储,用new创建
    int length;             //线性表当前长度
}SeqList;

//初始化传入的顺序表
Status SeqListInit(SeqList** list);
//判断传入的顺序表是否为空
Status SeqListEmpty(const SeqList* list);
//清空传入的顺序表
Status SeqListClear(SeqList* list);
//销毁传入的顺序表
Status SeqListDestroy(SeqList* list);
//获得顺序表list的第pos个位置的元素，用指针e返回
Status SeqListGetElem(const SeqList* list, int pos, ElemType* e);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int SeqListLocateElem(const SeqList* list, ElemType e);
//在顺序表中的pos位置插入元素e
Status SeqListInsert(SeqList* list, int pos, ElemType e);
//删除顺序表中的pos位置的元素，并用指针e返回
Status SeqListDelete(SeqList* list, int pos, ElemType* e);
//获得顺序表长度
int SeqListLength(const SeqList* list);
//遍历输出顺序表内容
Status SeqListOutput(const SeqList* list);

#endif // AHEAD_H_INCLUDED
