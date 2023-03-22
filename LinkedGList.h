#ifndef LINKEDGLIST_H_INCLUDED
#define LINKEDGLIST_H_INCLUDED

//里面有需要的枚举类型
#include "SubGList.h"

// 功　能：实现链式表示法广义表
// 设计者：李钰林
// 版本号：2018-10-12

typedef struct _LinkedGLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct _LinkedGLNode* hp;
	};
	struct _LinkedGLNode* tp;
}LinkedGLNode, *LinkedGList;

/*
因为链式广义表的特殊性（任何表表头特殊）
所以所有递归函数都需要子函数
*/

//初始化广义表（创建广义表）
Status LinkedGListInit(LinkedGList* L);
//求广义表的长度
int LinkedGListLength(LinkedGList* L);
//求广义表的深度
int LinkedGListDepth(LinkedGList* L);
//求广义表的深度子函数
int _LinkedGListDepth(LinkedGList* L);
//销毁广义表
Status LinkedGListDestroy(LinkedGList* L);
//广义表复制
Status LinkedGListCopy(LinkedGList* L, const LinkedGList* src);
//广义表复制子函数
Status _LinkedGListCopy(LinkedGList* L, const LinkedGList* src);
//判空
Status LinkedGListEmpty(LinkedGList* L);
//获取表头
Status LinkedGListGetHead(LinkedGList* head, const LinkedGList* L);
//获取表尾
Status LinkedGListGetTail(LinkedGList* tail, const LinkedGList* L);
//插入新表头
Status LinkedGListInsertHead(LinkedGList* L, const LinkedGList* e);
//删除原表头
Status LinkedGListDeleteHead(LinkedGList* L, LinkedGList* e);

//遍历广义表
Status LinkedGListTraverse(LinkedGList* L, Status (*visit)(AtomType*));
//简单打印
Status LinkedGListVisit(AtomType* a);

//由字符串创建广义表
//server方法在StaticStr.h里
Status LinkedGListCreate(LinkedGList* L, StaticStr* S);
//递归创建结点子函数
Status _LinkedGListCreate(LinkedGList* L, StaticStr* S);

#endif // LINKEDGLIST_H_INCLUDED
