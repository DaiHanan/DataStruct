#include "SeqList.h"


//初始化传入的顺序表
Status SeqListInit(SeqList** list){
    if(!list)
        return ERROR;
    if(*list == NULL){
        *list = (SeqList*)malloc(sizeof(SeqList));
    }
    if((*list)->data)
        free((*list)->data);
    (*list)->data = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
    if((*list)->data == NULL){
        printf("顺序表初始化失败！\n");
        return ERROR;
    }
    (*list)->length = 0;
    return OK;
}
//判断传入的顺序表是否为空
Status SeqListEmpty(const SeqList* list){
    if(list == NULL || list->data == NULL){
        return ERROR;
    }

    return list->length ? FALSE : TRUE;
}
//清空传入的顺序表
Status SeqListClear(SeqList* list){
    if(SeqListEmpty(list) == ERROR)
        return ERROR;
    list->length = 0;
    return OK;
}
//销毁传入的顺序表
Status SeqListDestroy(SeqList* list){
    if(SeqListClear(list) == ERROR)
        return ERROR;
    free(list->data);
    return OK;
}
//获得顺序表list的第pos个位置的元素，用指针e返回
Status SeqListGetElem(const SeqList* list, int pos, ElemType* e){
    if(SeqListEmpty(list) != FALSE || pos < 1 || pos > list->length + 1)
        return ERROR;
    *e = list->data[pos - 1];
    return OK;
}
//查找元素e的位置，如果找到返回返回元素位置，否则返回0,出错返回ERROR(-1)
int SeqListLocateElem(const SeqList* list, ElemType e){
    if(SeqListEmpty(list) != FALSE)
        return ERROR;
    for(int i = 0; i < list->length; i++){
        if(list->data[i] == e)
            return i + 1;
    }
    return 0;
}
//在顺序表中的pos位置插入元素e
Status SeqListInsert(SeqList* list, int pos, ElemType e){
    if(SeqListEmpty(list) ==  ERROR||
        pos < 1 ||
         pos > list->length + 1 ||
         list->length >= MAXSIZE)
        return ERROR;
    for(int i = list->length; i >= pos; i--){
        list->data[i] = list->data[i - 1];
    }
    list->data[pos - 1] = e;
    list->length++;
    return OK;
}
//删除顺序表中的pos位置的元素，并用指针e返回
Status SeqListDelete(SeqList* list, int pos, ElemType* e){
    if(SeqListEmpty(list) != FALSE || pos < 1 || pos > list->length || list->length >= MAXSIZE)
        return ERROR;
    *e = list->data[pos - 1];
    for(int i = pos - 1; i < list->length - 1; i++){
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return OK;
}
//获得顺序表长度
int SeqListLength(const SeqList* list){
    if(SeqListEmpty(list) == ERROR)
        return ERROR;
    return list->length;
}
//遍历输出顺序表内容
Status SeqListOutput(const SeqList* list){
    if(SeqListEmpty(list) == ERROR)
        return ERROR;
    if(list->length == 0){
        printf("顺序表为空！\n");
        return OK;
    }
    for(int i = 0; i < list->length; i++){
        printf("%d ", list->data[i]);
    }
    printf("\n");
    return OK;
}
