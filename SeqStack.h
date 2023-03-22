#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现顺序栈
// 设计者：李钰林
// 版本号：2018-10-03

#define MAXSIZE 100 //假设只能装100个元素

typedef struct _seqStack{
    ElemType data[MAXSIZE]; //顺序栈的数据数组
    int top;                //顺序栈栈顶下标
}SeqStack;

//初始化传入的顺序栈
Status SeqStackInit(SeqStack** stack);
//判断传入的顺序栈是否为空
Status SeqStackEmpty(const SeqStack* stack);
//判断传入的顺序栈是否为满
Status SeqStackFull(const SeqStack* stack);
//清空传入的顺序栈
Status SeqStackClear(SeqStack* stack);
//销毁传入的顺序栈
Status SeqStackDestroy(SeqStack* stack);
//获得顺序栈长度
int SeqStackLength(const SeqStack* stack);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int SeqStackLocateElem(const SeqStack* stack, ElemType e);
//入栈
Status SeqStackPush(SeqStack* stack, ElemType e);
//出栈
Status SeqStackPop(SeqStack* stack, ElemType* e);
//取栈顶元素
Status SeqStackTop(SeqStack* stack, ElemType* e);
//遍历输出顺序栈内容
Status SeqStackTraverse(SeqStack* stack, Status (*visit)(ElemType*));
//简单打印元素信息
Status SeqStackVisit(ElemType* e);

#endif // SEQSTACK_H_INCLUDED
