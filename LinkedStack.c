#include "LinkedStack.h"

//初始化传入的链表栈
Status LinkedStackInit(LinkedStack** stack){
    if(!stack)
        return ERROR;
    if(*stack)
        free(*stack);
    *stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if(*stack == NULL)    //分配内存失败
        return ERROR;
    (*stack)->top = NULL;
    (*stack)->length = 0;
    return OK;
}
//判断传入的链表栈是否为空
Status LinkedStackEmpty(const LinkedStack* stack){
    if(stack == NULL || stack->length < 0) //没有初始成功
        return ERROR;
    if(stack->length == 0 || stack->top == NULL)
        return TRUE;
    return FALSE;
}
//清空传入的链表栈
Status LinkedStackClear(LinkedStack* stack){
    if(!stack)
        return ERROR;
    sNode* p = stack->top; //指向栈顶节点
    while(p){
        sNode* q = p->next;
        free(p);
        p = q;
    }
    return OK;
}
//销毁传入的链表栈
Status LinkedStackDestroy(LinkedStack* stack){
    if(LinkedStackClear(stack) == ERROR) //清空内容
        return ERROR;
    //释放stack
    free(stack);
    return OK;
}
//获得链表栈长度
int LinkedStackLength(const LinkedStack* stack){
    if(!stack)
        return ERROR;
    return stack->length;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedStackLocateElem(const LinkedStack* stack, ElemType e){
    if(LinkedStackEmpty(stack) != FALSE)
        return ERROR;
    //当链表栈非空时搜索
    sNode* p = stack->top;//第一个元素
    int pos = 1;//记录元素位置
    while(p != NULL){
        if(p->data == e)
            return pos;
        p = p->next;
        pos++;
    }
    return 0;
}
//入栈
Status LinkedStackPush(LinkedStack* stack, ElemType e){
    if(!stack)
        return ERROR;
    sNode* newNode = (sNode*)malloc(sizeof(sNode));
    if(!newNode)
        return ERROR;
    newNode->data = e;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->length++;
    return OK;
}
//出栈
Status LinkedStackPop(LinkedStack* stack, ElemType* e){
    if(LinkedStackEmpty(stack) != FALSE)
        return ERROR;
    sNode* p = stack->top;
    stack->top = p->next;
    *e = p->data;
    free(p);
    stack->length--;
    return OK;
}
//取栈顶元素
Status LinkedStackTop(LinkedStack* stack, ElemType* e){
    if(LinkedStackEmpty(stack) != FALSE)
        return ERROR;
    *e = stack->top->data;
    return OK;
}
//遍历输出链表栈内容
Status LinkedStackTraverse(LinkedStack* stack, Status (*visit)(sNode*)){
    if(!stack)
        return ERROR;
    if(stack->length == 0){
        printf("链表栈为空！\n");
        return OK;
    }
    sNode* p = stack->top;
    while(p){
        if(visit(p) == ERROR)
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}
//简单打印元素信息
Status LinkedStackVisit(sNode* node){
    if(!node)
        return ERROR;
    printf("%d ", node->data);
    return OK;
}
