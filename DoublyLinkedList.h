#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现双向链表
// 设计者：李钰林
// 版本号：2018-09-24

typedef struct _dNode{   //结点定义
    ElemType data;
    struct _dNode* next;
    struct _dNode* prior;
}dNode;

typedef struct _doublyLinkedList{
    dNode* head;         //存储单链表的头结点
    int length;         //单链表当前长度
}DoublyLinkedList;

//初始化传入的双向链表
Status DoublyLinkedListInit(DoublyLinkedList** list);
//判断传入的双向链表是否为空
Status DoublyLinkedListEmpty(const DoublyLinkedList* list);
//清空传入的双向链表
Status DoublyLinkedListClear(DoublyLinkedList* list);
//销毁传入的双向链表
Status DoublyLinkedListDestroy(DoublyLinkedList* list);
//获得双向链表list的第pos个位置的元素，用指针e返回
Status DoublyLinkedListGetElem(const DoublyLinkedList* list, int pos, ElemType* e);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int DoublyLinkedListLocateElem(const DoublyLinkedList* list, ElemType e);
//在双向链表中的pos位置插入元素e
Status DoublyLinkedListInsert(DoublyLinkedList* list, int pos, ElemType e);
//删除双向链表中的pos位置的元素，并用指针e返回
Status DoublyLinkedListDelete(DoublyLinkedList* list, int pos, ElemType* e);
//获得双向链表长度
int DoublyLinkedListLength(const DoublyLinkedList* list);
//遍历输出双向链表内容
Status DoublyLinkedListTraverse(DoublyLinkedList* list, Status (*visit)(dNode*));
//简单打印结点信息
Status DoublyLinkedListVisit(dNode* node);

//双向链表特有：向前查找结点
//根据元素 e 返回指定结点node
Status DoublyLinkedListGetNode(const DoublyLinkedList* list, ElemType e, dNode** node);
//返回指定结点的前第n个结点node
dNode* DoublyLinkedListGetPreNode(const DoublyLinkedList* list, dNode* node, int n);

#endif // DOUBLYLINKEDLIST_H_INCLUDED
