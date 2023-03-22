#include "SeqStack.h"

//初始化传入的顺序栈
Status SeqStackInit(SeqStack** stack){
    if(!stack)
        return ERROR;
    if(*stack)
        free(*stack);
    (*stack) = (SeqStack*)malloc(sizeof(SeqStack));
    if(!(*stack))
        return ERROR;
    (*stack)->top = -1;
    return OK;
}
//判断传入的顺序栈是否为空
Status SeqStackEmpty(const SeqStack* stack){
    if(!stack)
        return ERROR;
    return stack->top == -1 ? TRUE : FALSE;
}
//判断传入的顺序栈是否为满
Status SeqStackFull(const SeqStack* stack){
    if(!stack)
        return ERROR;
    return stack->top == MAXSIZE - 1 ? TRUE : FALSE;
}
//清空传入的顺序栈
Status SeqStackClear(SeqStack* stack){
    if(!stack)
        return ERROR;
    stack->top = -1;
    return OK;
}
//销毁传入的顺序栈
Status SeqStackDestroy(SeqStack* stack){
    if(!stack)
        return ERROR;
    free(stack);
    return OK;
}
//获得顺序栈长度
int SeqStackLength(const SeqStack* stack){
    if(!stack)
        return ERROR;
    return stack->top + 1;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int SeqStackLocateElem(const SeqStack* stack, ElemType e){
    if(SeqStackEmpty(stack) != FALSE)
        return ERROR;
    for(int i = 0; i <= stack->top; i++){
        if(stack->data[i] == e)
            return i + 1;
    }
    return 0;
}
//入栈
Status SeqStackPush(SeqStack* stack, ElemType e){
    if(SeqStackFull(stack) != FALSE)
        return ERROR;
    stack->data[++stack->top] = e;
    return OK;
}
//出栈
Status SeqStackPop(SeqStack* stack, ElemType* e){
    if(SeqStackEmpty(stack) != FALSE)
        return ERROR;
    *e = stack->data[stack->top--];
    return OK;
}
//取栈顶元素
Status SeqStackTop(SeqStack* stack, ElemType* e){
    if(SeqStackEmpty(stack) != FALSE)
        return ERROR;
    *e = stack->data[stack->top];
    return OK;
}
//遍历输出顺序栈内容
Status SeqStackTraverse(SeqStack* stack, Status (*visit)(ElemType*)){
    if(!stack)
        return ERROR;
    if(stack->top == -1){
        printf("顺序栈为空！\n");
        return OK;
    }
    for(int i = stack->top; i >= 0; i--){
        if(visit(&stack->data[i]) == ERROR)
            return ERROR;
    }
    printf("\n");
    return OK;
}
//简单打印元素信息
Status SeqStackVisit(ElemType* e){
    if(!e)
        return ERROR;
    printf("%d ", *e);
}
