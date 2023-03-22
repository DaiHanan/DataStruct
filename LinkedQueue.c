#include "LinkedQueue.h"

//初始化传入的链式队列
Status LinkedQueueInit(LinkedQueue** queue){
    if(!queue)
        return ERROR;
    if(*queue)
        free(*queue);
    *queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if(*queue == NULL)    //分配内存失败
        return ERROR;
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->length = 0;
    return OK;
}
//判断传入的链式队列是否为空
Status LinkedQueueEmpty(const LinkedQueue* queue){
    if(!queue || queue->length < 0)
        return ERROR;
    return queue->length == 0 ? TRUE :FALSE;
}
//清空传入的链式队列
Status LinkedQueueClear(LinkedQueue* queue){
    if(!queue)
        return ERROR;
    qNode* p = queue->front;
    while(p){
        qNode*q = p->next;
        free(p);
        p = q;
    }
    return OK;
}
//销毁传入的链式队列
Status LinkedQueueDestroy(LinkedQueue* queue){
    if(LinkedQueueClear(queue) == ERROR)//清空内容
        return ERROR;
    //清空链表
    free(queue);
    return OK;
}
//获得链式队列长度
int LinkedQueueLength(const LinkedQueue* queue){
    if(!queue || queue->length < 0)
        return ERROR;
    return queue->length;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedQueueLocateElem(const LinkedQueue* queue, ElemType e){
    if(LinkedQueueEmpty(queue) != FALSE)
        return ERROR;
        qNode* p = queue->front;
    for(int i = 0; i < queue->length; i++){
        if(p->data == e)
            return i + 1;
        p = p->next;
    }
    return 0;
}
//入队列
Status LinkedQueuePush(LinkedQueue* queue, ElemType e){
    if(!queue)
        return ERROR;
    qNode* newNode = (qNode*)malloc(sizeof(qNode));
    if(!newNode)
        return ERROR;
    newNode->next = NULL; //设置新节点信息
    newNode->data = e;
    if(queue->length == 0){//没有元素时
        queue->front = newNode;
        queue->rear = newNode;
    }
    else{
    queue->rear->next = newNode;//关联rear节点
    queue->rear = newNode;
    }
    queue->length++;//修改长度
    return OK;
}
//出队列
Status LinkedQueuePop(LinkedQueue* queue, ElemType* e){
    if(LinkedQueueEmpty(queue) != FALSE)
        return ERROR;
    qNode* p = queue->front;//临时存储出队节点
    queue->front = p->next;
    *e = p->data;
    free(p);
    if(queue->length == 1)//此时rear是野指针
        queue->rear = NULL;
    queue->length--;
    return OK;
}
//取队列首元素
Status LinkedQueueTop(LinkedQueue* queue, ElemType* e){
    if(LinkedQueueEmpty(queue) != FALSE)
        return ERROR;
    *e = queue->front->data;
    return OK;
}
//遍历输出链式队列内容
Status LinkedQueueTraverse(LinkedQueue* queue, Status (*visit)(qNode*)){
    if(!queue)
        return ERROR;
    if(queue->length == 0){
        printf("链式队列为空！\n");
        return OK;
    }
    qNode* p = queue->front;
    while(p){
        if(visit(p) == ERROR)
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}
//简单打印元素信息
Status LinkedQueueVisit(qNode* node){
    if(!node)
        return ERROR;
    printf("%d ", node->data);
    return OK;
}
