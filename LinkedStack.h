#ifndef LINKEDSTACK_H_INCLUDED
#define LINKEDSTACK_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现链表栈
// 设计者：李钰林
// 版本号：2018-10-04

typedef struct _sNode{
    ElemType data;
    struct _sNode* next;
}sNode;

typedef struct _linkedStack{
    sNode* top;     //存储链表栈的栈顶指针
    int length;     //链表栈当前长度
}LinkedStack;

//初始化传入的链表栈
Status LinkedStackInit(LinkedStack** stack);
//判断传入的链表栈是否为空
Status LinkedStackEmpty(const LinkedStack* stack);
//清空传入的链表栈
Status LinkedStackClear(LinkedStack* stack);
//销毁传入的链表栈
Status LinkedStackDestroy(LinkedStack* stack);
//获得链表栈长度
int LinkedStackLength(const LinkedStack* stack);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedStackLocateElem(const LinkedStack* stack, ElemType e);
//入栈
Status LinkedStackPush(LinkedStack* stack, ElemType e);
//出栈
Status LinkedStackPop(LinkedStack* stack, ElemType* e);
//取栈顶元素
Status LinkedStackTop(LinkedStack* stack, ElemType* e);
//遍历输出链表栈内容
Status LinkedStackTraverse(LinkedStack* stack, Status (*visit)(sNode*));
//简单打印元素信息
Status LinkedStackVisit(sNode* node);

#endif // LINKEDSTACK_H_INCLUDED
