#ifndef LINKEDQUEUE_H_INCLUDED
#define LINKEDQUEUE_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现链式队列
// 设计者：李钰林
// 版本号：2018-10-04

typedef struct _qNode{
    ElemType data;
    struct _qNode* next;
}qNode;

typedef struct _linkedQueue{
    qNode* front;                //链式队列首元素节点
    qNode* rear;                 //链式队列尾元素节点
    int length;
}LinkedQueue;

//初始化传入的链式队列
Status LinkedQueueInit(LinkedQueue** queue);
//判断传入的链式队列是否为空
Status LinkedQueueEmpty(const LinkedQueue* queue);
//清空传入的链式队列
Status LinkedQueueClear(LinkedQueue* queue);
//销毁传入的链式队列
Status LinkedQueueDestroy(LinkedQueue* queue);
//获得链式队列长度
int LinkedQueueLength(const LinkedQueue* queue);
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedQueueLocateElem(const LinkedQueue* queue, ElemType e);
//入队列
Status LinkedQueuePush(LinkedQueue* queue, ElemType e);
//出队列
Status LinkedQueuePop(LinkedQueue* queue, ElemType* e);
//取队列首元素
Status LinkedQueueTop(LinkedQueue* queue, ElemType* e);
//遍历输出链式队列内容
Status LinkedQueueTraverse(LinkedQueue* queue, Status (*visit)(qNode*));
//简单打印元素信息
Status LinkedQueueVisit(qNode* node);

#endif // LINKEDQUEUE_H_INCLUDED
