#ifndef LOOPLINKEDLIST_H_INCLUDED
#define LOOPLINKEDLIST_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现循环链表
// 设计者：李钰林
// 版本号：2018-10-03

typedef struct _lnode{   //结点定义
    ElemType data;
    struct _lnode* next;
}lNode;

typedef struct _loopLinkedList{
    lNode* head;         //存储循环链表的头结点
    int length;         //单链表当前长度
}LoopLinkedList;

//循环链表大多数操作和单链表相似

//初始化传入的循环链表
Status LoopLinkedListInit(LoopLinkedList** list);
//判断传入的循环链表是否为空
Status LoopLinkedListEmpty(const LoopLinkedList* list);
//清空传入的循环链表
Status LoopLinkedListClear(LoopLinkedList* list);
//销毁传入的循环链表
Status LoopLinkedListDestroy(LoopLinkedList* list);
//获得循环链表list的第pos个位置的元素，用指针e返回
Status LoopLinkedListGetElem(const LoopLinkedList* list, int pos, ElemType* e);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LoopLinkedListLocateElem(const LoopLinkedList* list, ElemType e);
//在循环链表中的pos位置插入元素e
Status LoopLinkedListInsert(LoopLinkedList* list, int pos, ElemType e);
//删除循环链表中的pos位置的元素，并用指针e返回
Status LoopLinkedListDelete(LoopLinkedList* list, int pos, ElemType* e);
//获得循环链表长度
int LoopLinkedListLength(const LoopLinkedList* list);

//根据元素 e 返回指定结点node
Status LoopLinkedListGetNode(const LoopLinkedList* list, ElemType e, lNode** node);
//循环链表特有:从任一位置开始循环访问所有元素
//从位置pos开始访问所有元素
Status LoopLinkedListTraverse(LoopLinkedList* list, int pos, Status (*visit)(lNode*));
//简单打印结点信息
Status LoopLinkedListVisit(lNode* node);

#endif // LOOPLINKEDLIST_H_INCLUDED
