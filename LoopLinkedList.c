#include "LoopLinkedList.h"

//初始化传入的循环链表
Status LoopLinkedListInit(LoopLinkedList** list){
    if(!list)
        return ERROR;
    LinkedListDestroy(*list);//先释放所有空间
    *list = (LoopLinkedList*)malloc(sizeof(LoopLinkedList));
    if(*list == NULL)    //分配内存失败
        return ERROR;
    (*list)->head = (lNode*)malloc(sizeof(lNode));
    if((*list)->head == NULL)  //分配内存失败
        return ERROR;
    (*list)->head->next = NULL;
    (*list)->head->data = 0;
    (*list)->length = 0;
    return OK;
}
//判断传入的循环链表是否为空
Status LoopLinkedListEmpty(const LoopLinkedList* list){
    if(list == NULL || list->head == NULL) //没有初始成功
        return ERROR;
    if(list->length == 0 || list->head->next == NULL)
        return TRUE;
    return FALSE;
}
//清空传入的循环链表
Status LoopLinkedListClear(LoopLinkedList* list){
    if(LoopLinkedListEmpty(list) == ERROR) //只有当链表不为空时才需清空
        return ERROR;
    if(list->length == 0)
        return OK;
    lNode* p = list->head->next; //指向第一个数据
    lNode* q;
    for(int i = 0; i < list->length; i++){
        q = p->next;
        free(p);
        p = q;
    }
    list->head->next = NULL;
    return OK;
}
//销毁传入的循环链表
Status LoopLinkedListDestroy(LoopLinkedList* list){
    if(LoopLinkedListClear(list) == ERROR) //清空循环链表内容
        return ERROR;
    free(list->head);
    free(list);
    //list = NULL;  按值传递，修改无效
    return OK;
}
//获得循环链表list的第pos个位置的元素，用指针e返回
Status LoopLinkedListGetElem(const LoopLinkedList* list, int pos, ElemType* e){
    if(LoopLinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且循环链表非空才继续
    lNode* p = list->head;
    for(int i = 0; i < pos; i++){
        p = p->next;
    }
    *e = p->data;
    return OK;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LoopLinkedListLocateElem(const LoopLinkedList* list, ElemType e){
    if(LoopLinkedListEmpty(list) != FALSE)
        return ERROR;
    //当循环链表非空时搜索
    lNode* p = list->head->next;//第一个元素
    for(int i = 0; i < list->length; i++){
        if(p->data == e)
            return i + 1;
        p = p->next;
    }
    return 0;
}
//在循环链表中的pos位置插入元素e
Status LoopLinkedListInsert(LoopLinkedList* list, int pos, ElemType e){
    if(LoopLinkedListEmpty(list) == ERROR
        || pos > list->length + 1
         || pos < 1)
        return ERROR;
    //当pos恰当且循环链表非空才继续
    lNode* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    lNode* newNode = (lNode*)malloc(sizeof(lNode));
    if(newNode == NULL)//内存申请失败
        return ERROR;

    newNode->data = e;
    newNode->next = p->next;    //修改2个指针，两步操作
    if(list->length == 0)
        newNode->next = newNode;
    p->next = newNode;
    list->length++;//修改长度
    return OK;
}
//删除循环链表中的pos位置的元素，并用指针e返回
Status LoopLinkedListDelete(LoopLinkedList* list, int pos, ElemType* e){
    if(LoopLinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且循环链表非空才继续
    lNode* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    lNode* delNode = p->next;
    p->next = delNode->next; //修改删除结点前结点指针
    *e = delNode->data;      //返回指定元素
    free(delNode);
    delNode = NULL; // 清除空指针
    list->length--;//修改长度
    return OK;
}
//获得循环链表长度
int LoopLinkedListLength(const LoopLinkedList* list){
    if(LoopLinkedListEmpty(list) == ERROR)
        return ERROR;
    return list->length;
}

//根据元素 e 返回指定结点node
Status LoopLinkedListGetNode(const LoopLinkedList* list, ElemType e, lNode** node){
    if(LoopLinkedListEmpty(list) != FALSE)
        return ERROR;
    //当链表非空时搜索
    lNode* p = list->head->next;//第一个元素
    while(p != NULL){
        if(p->data == e)
            break;
        p = p->next;
    }
    *node = p; //找不到就赋值为NULL
    return p == NULL ? ERROR : OK;
}
//循环链表特有:从任一位置开始循环访问所有元素
//从位置pos开始访问所有元素
Status LoopLinkedListTraverse(LoopLinkedList* list, int pos, Status (*visit)(lNode*)){
     if(LoopLinkedListEmpty(list) == ERROR)
        return ERROR;
    if(list->length == 0){
        printf("循环链表为空！\n");
        return OK;
    }
    if(pos > list->length || pos < 1){
        return ERROR;
    }
    //当pos恰当且循环链表非空才继续
    lNode* p = list->head;
    for(int i = 0; i < pos; i++){ //找到pos位置节点
        p = p->next;
    }
    for(int i = 0; i < list->length; i++){
        if(visit(p) == ERROR)
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}
//简单打印结点信息
Status LoopLinkedListVisit(lNode* node){
    if(!node)
        return ERROR;
    printf("%d ", node->data);
    return OK;
}
