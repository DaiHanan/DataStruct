#include "SeqQueue.h"

//初始化传入的顺序队列
Status SeqQueueInit(SeqQueue** queue){
    if(!queue)
        return ERROR;
    if(*queue)
        free(queue);
    (*queue) = (SeqQueue*)malloc(sizeof(SeqQueue));
    if(!(*queue))
        return ERROR;
    (*queue)->front = 0;
    (*queue)->rear = 0;
    return OK;
}
//判断传入的顺序队列是否为空
Status SeqQueueEmpty(const SeqQueue* queue){
    if(!queue)
        return ERROR;
    return queue->rear == queue->front ? TRUE : FALSE;
}
//判断传入的顺序队列是否为满
Status SeqQueueFull(const SeqQueue* queue){
    if(!queue)
        return ERROR;
    return (queue->rear + 1) % MAXSIZE == queue->front ? TRUE : FALSE;
}
//清空传入的顺序队列
Status SeqQueueClear(SeqQueue* queue){
    if(!queue)
        return ERROR;
    queue->front = 0;
    queue->rear = 0;
}
//销毁传入的顺序队列
Status SeqQueueDestroy(SeqQueue* queue){
    if(!queue)
        return ERROR;
    free(queue);
    return OK;
}
//获得顺序队列长度
int SeqQueueLength(const SeqQueue* queue){
    if(!queue)
        return ERROR;
    return (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int SeqQueueLocateElem(const SeqQueue* queue, ElemType e){
    if(!queue)
        return ERROR;
    int i = queue->front;
    while(i != queue->rear){ //i是当前下标
        if(queue->data[i] == e)
            return (i - queue->front + MAXSIZE) % MAXSIZE + 1; //返回元素e的位置
        i = (i + 1) % MAXSIZE;
    }
    return 0;
}
//入队列
Status SeqQueuePush(SeqQueue* queue, ElemType e){
    if(SeqQueueFull(queue) != FALSE)
        return ERROR;
    queue->data[queue->rear] = e;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return OK;
}
//出队列
Status SeqQueuePop(SeqQueue* queue, ElemType* e){
    if(SeqQueueEmpty(queue) != FALSE)
        return ERROR;
    *e = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    return OK;
}
//取队列首元素
Status SeqQueueTop(SeqQueue* queue, ElemType* e){
    if(SeqQueueEmpty(queue) != FALSE)
        return ERROR;
    *e = queue->data[queue->front];
    return OK;
}
//遍历输出顺序队列内容
Status SeqQueueTraverse(SeqQueue* queue, Status (*visit)(ElemType*)){
    if(!queue)
        return ERROR;
    if(SeqQueueEmpty(queue) == TRUE){
        printf("顺序队列为空！\n");
        return OK;
    }
    int i = queue->front;
    while(i != queue->rear){ //i是当前下标
        if(visit(&queue->data[i]) == ERROR)
            return ERROR;
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}
//简单打印元素信息
Status SeqQueueVisit(ElemType* e){
    if(!e)
        return ERROR;
    printf("%d ", *e);
}






