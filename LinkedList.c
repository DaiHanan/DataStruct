#include "LinkedList.h"

//初始化传入的单链表
Status LinkedListInit(LinkedList** list){
    if(!list)
        return ERROR;
    LinkedListDestroy(*list);//先释放所有空间
    *list = (LinkedList*)malloc(sizeof(LinkedList));
    if(*list == NULL)    //分配内存失败
        return ERROR;
    (*list)->head = (Node*)malloc(sizeof(Node));
    if((*list)->head == NULL)  //分配内存失败
        return ERROR;
    (*list)->head->next = NULL;
    (*list)->head->data = 0;
    (*list)->length = 0;
    return OK;
}
//判断传入的单链表是否为空
Status LinkedListEmpty(const LinkedList* list){
    if(list == NULL || list->head == NULL) //没有初始成功
        return ERROR;
    if(list->length == 0 || list->head->next == NULL)
        return TRUE;
    return FALSE;
}
//清空传入的单链表
Status LinkedListClear(LinkedList* list){
    if(LinkedListEmpty(list) == ERROR) //只有当链表不为空时才需清空
        return ERROR;
    if(list->length == 0)
        return OK;
    Node* p = list->head->next; //指向第一个数据
    Node* q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    list->head->next = NULL;
    return OK;
}
//销毁传入的单链表
Status LinkedListDestroy(LinkedList* list){
    if(LinkedListClear(list) == ERROR) //清空单链表内容
        return ERROR;
    free(list->head);
    free(list);
    //list = NULL;  按值传递，修改无效
    return OK;
}
//获得单链表list的第pos个位置的元素，用指针e返回
Status LinkedListGetElem(const LinkedList* list, int pos, ElemType* e){
    if(LinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且单链表非空才继续
    Node* p = list->head;
    for(int i = 0; i < pos; i++){
        p = p->next;
    }
    *e = p->data;
    return OK;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0
int LinkedListLocateElem(const LinkedList* list, ElemType e){
    if(LinkedListEmpty(list) != FALSE)
        return ERROR;
    //当单链表非空时搜索
    Node* p = list->head->next;//第一个元素
    int pos = 1;//记录元素位置
    while(p != NULL){
        if(p->data == e)
            return pos;
        p = p->next;
        pos++;
    }
    return 0;
}
//在单链表中的pos位置插入元素e
Status LinkedListInsert(LinkedList* list, int pos, ElemType e){
    if(LinkedListEmpty(list) == ERROR
        || pos > list->length + 1
         || pos < 1)
        return ERROR;
    //当pos恰当且单链表非空才继续
    Node* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)//内存申请失败
        return ERROR;
    newNode->data = e;
    newNode->next = p->next;    //修改2个指针，两步操作
    p->next = newNode;
    list->length++;//修改长度
    return OK;
}
//删除单链表中的pos位置的元素，并用指针e返回
Status LinkedListDelete(LinkedList* list, int pos, ElemType* e){
    if(LinkedListEmpty(list) != FALSE || pos > list->length || pos < 1)
        return ERROR;
    //当pos恰当且单链表非空才继续
    Node* p = list->head;
    for(int i = 0; i < pos - 1; i++){   //找到pos前一个位置的结点
        p = p->next;
    }
    Node* delNode = p->next;
    p->next = delNode->next; //修改删除结点前结点指针
    *e = delNode->data;      //返回指定元素
    free(delNode);
    delNode = NULL; // 清除空指针
    list->length--;//修改长度
    return OK;
}
//获得单链表长度
int LinkedListLength(const LinkedList*list){
    if(LinkedListEmpty(list) == ERROR)
        return ERROR;
    return list->length;
}
//遍历输出单链表内容
Status LinkedListTraverse(LinkedList* list, Status (*visit)(Node*)){
    if(LinkedListEmpty(list) == ERROR)
        return ERROR;
    if(list->length == 0){
        printf("单链表为空！\n");
        return OK;
    }
    Node* p = list->head->next; //第一个元素
    while(p != NULL){
        if(visit(p) == ERROR)
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}
//简单打印结点信息
Status LinkedListVisit(Node* node){
    if(!node)
        return ERROR;
    printf("%d ", node->data);
    return OK;
}
