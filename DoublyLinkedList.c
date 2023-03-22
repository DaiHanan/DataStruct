#include "DoublyLinkedList.h"

//初始化传入的双向链表
Status DoublyLinkedListInit(DoublyLinkedList** list){
    if(!list)
        return ERROR;
    DoublyLinkedListDestroy(*list);//先释放所有空间
    *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if(*list == NULL)    //分配内存失败
        return ERROR;
    (*list)->head = (dNode*)malloc(sizeof(dNode));
    if((*list)->head == NULL)  //分配内存失败
        return ERROR;
    (*list)->head->next = NULL;
    (*list)->head->prior = NULL;
    (*list)->head->data = 0;
    (*list)->length = 0;
    return OK;
}
//判断传入的双向链表是否为空
Status DoublyLinkedListEmpty(const DoublyLinkedList* list){
    if(list == NULL || list->head == NULL) //没有初始成功
        return ERROR;
    if(list->length == 0 || list->head->next == NULL)
        return TRUE;
    return FALSE;
}
//清空传入的双向链表
Status DoublyLinkedListClear(DoublyLinkedList* list){
    if(DoublyLinkedListEmpty(list) == ERROR) //只有当链表不为空时才需清空
        return ERROR;
    if(list->length == 0)
        return OK;
    dNode* p = list->head->next; //指向第一个数据
    dNode* q;
    while(p != NULL){
        q = p->next;
        //q->prior = NULL;   释放内存，不需要修改prior了
        free(p);
        p = q;
    }
    list->head->next = NULL;
    return OK;
}
//销毁传入的双向链表
Status DoublyLinkedListDestroy(DoublyLinkedList* list){
    if(DoublyLinkedListClear(list) == ERROR) //清空链表内容
        return ERROR;
    free(list->head);
    free(list);
    //list = NULL;  按值传递，修改无效
    return OK;
}
//获得双向链表list的第pos个位置的元素，用指针e返回
Status DoublyLinkedListGetElem(const DoublyLinkedList* list, int pos, ElemType* e){
    if(DoublyLinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且链表非空才继续
    dNode* p = list->head;
    for(int i = 0; i < pos; i++){
        p = p->next;
    }
    *e = p->data;
    return OK;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int DoublyLinkedListLocateElem(const DoublyLinkedList* list, ElemType e){
    if(DoublyLinkedListEmpty(list) != FALSE)
        return ERROR;
    //当链表非空时搜索
    dNode* p = list->head->next;//第一个元素
    int pos = 1;//记录元素位置
    while(p != NULL){
        if(p->data == e)
            return pos;
        p = p->next;
        pos++;
    }
    return 0;
}
//在双向链表中的pos位置插入元素e
Status DoublyLinkedListInsert(DoublyLinkedList* list, int pos, ElemType e){
    if(DoublyLinkedListEmpty(list) == ERROR
        || pos > list->length + 1
         || pos < 1)
        return ERROR;
    //当pos恰当且链表非空才继续
    dNode* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    dNode* newNode = (dNode*)malloc(sizeof(dNode));
    if(newNode == NULL)//内存申请失败
        return ERROR;
    newNode->data = e;
    newNode->next = p->next;
    newNode->prior = p;
    if(p->next != NULL)
        p->next->prior = newNode;   //修改4个指针，四步操作
    p->next = newNode;
    list->length++;//修改长度
    return OK;
}
//删除双向链表中的pos位置的元素，并用指针e返回
Status DoublyLinkedListDelete(DoublyLinkedList* list, int pos, ElemType* e){
    if(DoublyLinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且链表非空才继续
    dNode* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    dNode* delNode = p->next;
    delNode->next->prior = p;
    p->next = delNode->next;    //修改删除结点前后两个结点指针
    *e = delNode->data;         //返回指定元素
    free(delNode);
    delNode = NULL; // 清除空指针
    list->length--;//修改长度
    return OK;
}
//获得双向链表长度
int DoublyLinkedListLength(const DoublyLinkedList* list){
    if(DoublyLinkedListEmpty(list) == ERROR)
        return ERROR;
    return list->length;
}
//遍历输出双向链表内容
Status DoublyLinkedListTraverse(DoublyLinkedList* list, Status (*visit)(dNode*)){
if(DoublyLinkedListEmpty(list) == ERROR)
        return ERROR;
    if(list->length == 0){
        printf("双向链表为空！\n");
        return OK;
    }
    dNode* p = list->head->next; //第一个元素
    while(p != NULL){
        if(visit(p) == ERROR)
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}
//简单打印结点信息
Status DoublyLinkedListVisit(dNode* node){
    if(!node)
        return ERROR;
    printf("%d ", node->data);
    return OK;
}

//双向链表特有：向前查找结点
//根据元素 e 返回指定结点node
Status DoublyLinkedListGetNode(const DoublyLinkedList* list, ElemType e, dNode** node){
     if(DoublyLinkedListEmpty(list) != FALSE)
        return ERROR;
    //当链表非空时搜索
    dNode* p = list->head->next;//第一个元素
    while(p != NULL){
        if(p->data == e)
            break;
        p = p->next;
    }
    *node = p; //找不到就赋值为NULL
    return p == NULL ? ERROR : OK;
}
//返回指定结点的前第n个结点node
dNode* DoublyLinkedListGetPreNode(const DoublyLinkedList* list, dNode* node, int n){
    if(DoublyLinkedListEmpty(list) != FALSE || node == NULL)
        return ERROR;
    //当链表非空且结点非空时搜索
    //dNode* p = node;
    for(int i = 0; i < n; i++){
            if(node->prior == list->head)
            return NULL;
        node = node->prior;
    }
    return node;
}
