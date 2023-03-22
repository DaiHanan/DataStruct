#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现（动态）顺序队列 （循环链表）
// 设计者：李钰林
// 版本号：2018-10-04

#define MAXSIZE 100 //假设只能装100 - 1个元素，为了方便判断

typedef struct _seqQueue{
    ElemType data[MAXSIZE]; //顺序队列的数据数组
    int front;                //顺序队列首元素下标
    int rear;                 //顺序队列尾元素下标
}SeqQueue;

//初始化传入的顺序队列
Status SeqQueueInit(SeqQueue** queue);
//判断传入的顺序队列是否为空
Status SeqQueueEmpty(const SeqQueue* queue);
//判断传入的顺序队列是否为满
Status SeqQueueFull(const SeqQueue* queue);
//清空传入的顺序队列
Status SeqQueueClear(SeqQueue* queue);
//销毁传入的顺序队列
Status SeqQueueDestroy(SeqQueue* queue);
//获得顺序队列长度
int SeqQueueLength(const SeqQueue* queue);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int SeqQueueLocateElem(const SeqQueue* queue, ElemType e);
//入队列
Status SeqQueuePush(SeqQueue* queue, ElemType e);
//出队列
Status SeqQueuePop(SeqQueue* queue, ElemType* e);
//取队列首元素
Status SeqQueueTop(SeqQueue* queue, ElemType* e);
//遍历输出顺序队列内容
Status SeqQueueTraverse(SeqQueue* queue, Status (*visit)(ElemType*));
//简单打印元素信息
Status SeqQueueVisit(ElemType* e);

#endif // SEQQUEUE_H_INCLUDED
