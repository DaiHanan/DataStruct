#ifndef SUBGLIST_H_INCLUDED
#define SUBGLIST_H_INCLUDED

#include "MyDefinition.h"

#include "StaticStr.h" //因为需要字符串操作，用了一个字符串数据结构

// 功　能：实现子表表示法广义表
// 设计者：李钰林
// 版本号：2018-10-07

typedef char AtomType;

typedef enum{
    ATOM, LIST  //ATOM == 0（原子）、LIST == 1（子表）
}ElemTag;

typedef struct _subGLNode{
    ElemTag tag;                    //用来区分原子结点和表结点
    union{                          //原子结点和表结点联合部分
        AtomType atom;              //原子结点的值
        struct{
            struct _subGLNode* hp, *tp; //表结点的指针域，hp、tp指向表头表尾
        }ptr;
    };
}*SubGList, SubGLNode;

//初始化广义表（创建广义表）
Status SubGListInit(SubGList* L);
//求广义表的长度
int SubGListLength(SubGList* L);
//求广义表的深度
int SubGListDepth(SubGList* L);
//销毁广义表
Status SubGListDestroy(SubGList* L);
//广义表复制
Status SubGListCopy(SubGList* L, const SubGList* src);
//判空
Status SubGListEmpty(SubGList* L);
//获取表头
Status SubGListGetHead(SubGList* head, const SubGList* L);
//获取表尾
Status SubGListGetTail(SubGList* tail, const SubGList* L);
//插入新表头
Status SubGListInsertHead(SubGList* L, const SubGList* e);
//删除原表头
Status SubGListDeleteHead(SubGList* L, SubGList* e);

//遍历广义表
Status SubGListTraverse(SubGList* L, Status (*visit)(AtomType*));
//简单打印
Status SubGListVisit(AtomType* a);

//由字符串创建广义表
//server方法在StaticStr.h里
Status SubGListCreate(SubGList* L, StaticStr* S);


#endif // SUBGLIST_H_INCLUDED
