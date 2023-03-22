#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现单链表
// 设计者：李钰林
// 版本号：2018-09-24

typedef struct _node{   //结点定义
    ElemType data;
    struct _node* next;
}Node;

typedef struct _linkedList{
    Node* head;         //存储单链表的头结点
    int length;         //单链表当前长度
}LinkedList;

//初始化传入的单链表
Status LinkedListInit(LinkedList** list);
//判断传入的单链表是否为空
Status LinkedListEmpty(const LinkedList* list);
//清空传入的单链表
Status LinkedListClear(LinkedList* list);
//销毁传入的单链表
Status LinkedListDestroy(LinkedList* list);
//获得单链表list的第pos个位置的元素，用指针e返回
Status LinkedListGetElem(const LinkedList* list, int pos, ElemType* e);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedListLocateElem(const LinkedList* list, ElemType e);
//在单链表中的pos位置插入元素e
Status LinkedListInsert(LinkedList* list, int pos, ElemType e);
//删除单链表中的pos位置的元素，并用指针e返回
Status LinkedListDelete(LinkedList* list, int pos, ElemType* e);
//获得单链表长度
int LinkedListLength(const LinkedList* list);
//遍历输出单链表内容
Status LinkedListTraverse(LinkedList* list, Status (*visit)(Node*));
//简单打印结点信息
Status LinkedListVisit(Node* node);

#endif // LINKEDLIST_H_INCLUDED
