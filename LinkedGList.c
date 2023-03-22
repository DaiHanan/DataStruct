#include "LinkedGList.h"

//初始化广义表（创建广义表）
Status LinkedGListInit(LinkedGList* L){
    if(!L)
        return ERROR;
    LinkedGListDestroy(L);//先释放空间
    *L = (LinkedGLNode*)malloc(sizeof(LinkedGLNode));
    if(!*L)
        return OVERFLOW;
    (*L)->tag = LIST;
    (*L)->hp = (*L)->tp = NULL;
    return OK;
}
//求广义表的长度
int LinkedGListLength(LinkedGList* L){
    if(!L)
        return ERROR;
    if(!(*L)->hp)
        return 0;
    int len = 0;
    LinkedGLNode* p = (*L)->hp;
    while(p){
        len++;
        p = p->tp;
    }
    return len;
}
//求广义表的深度
int LinkedGListDepth(LinkedGList* L){
    if(!L)
        return ERROR;
    return _LinkedGListDepth(&((*L)->hp));
}
//求广义表的深度子函数
int _LinkedGListDepth(LinkedGList* L){
    if(!*L)
        return 1;
    int max, dep = 0;
    LinkedGLNode* p;
    for(max = 0, p = *L; p; p = p->tp){
        if(p->tag == LIST && p->hp)//当p是LIST且p不是空表时递归
            dep = _LinkedGListDepth(&p->hp);
        max = dep > max ? dep : max;
    }
    return max + 1;
}
//销毁广义表
Status LinkedGListDestroy(LinkedGList* L){
    if(!L)
        return ERROR;
    if(!*L)
        return OK;
    if((*L)->tag == LIST){
        if(LinkedGListDestroy(&((*L)->hp)) != OK)
            return ERROR;
    }
    if(LinkedGListDestroy(&((*L)->tp)) != OK)
        return ERROR;
    free(*L);
    return OK;
}
//广义表复制
Status LinkedGListCopy(LinkedGList* L, const LinkedGList* src){
    if(!L || !src)
        return ERROR;
    if(LinkedGListInit(L) == OVERFLOW)//初始化失败
        return OVERFLOW;
    return _LinkedGListCopy(&((*L)->hp), &((*src)->hp));
}
//广义表复制子函数
Status _LinkedGListCopy(LinkedGList* L, const LinkedGList* src){
    if(!*src){
        *L = NULL;
        return OK;
    }
    *L = (LinkedGLNode*)malloc(sizeof(LinkedGLNode));
    if(!*L)
        return OVERFLOW;
    (*L)->tag = (*src)->tag;
    if((*src)->tag == LIST){
        if(_LinkedGListCopy(&((*L)->hp), &((*src)->hp)) == OVERFLOW)
            return OVERFLOW;
    }
    else{
        (*L)->atom = (*src)->atom;
    }
    if(_LinkedGListCopy(&((*L)->tp), &((*src)->tp)) == OVERFLOW)
        return OVERFLOW;
    return OK;
}
//判空
Status LinkedGListEmpty(LinkedGList* L){
    if(!L)
        return ERROR;
    return (*L)->hp ? FALSE : TRUE;
}
//获取表头
Status LinkedGListGetHead(LinkedGList* head, const LinkedGList* L){
    if(!head || !L || LinkedGListEmpty(L) != FALSE)
        return ERROR;
    //当表存在且不为空时继续
    LinkedGLNode* p = (*L)->hp->tp;
    (*L)->hp->tp = NULL;
    if(LinkedGListCopy(head, L) != OK){//复制表头
        (*L)->hp->tp = p;
        return ERROR;
    }
    (*L)->hp->tp = p;
    return OK;
}
//获取表尾
Status LinkedGListGetTail(LinkedGList* tail, const LinkedGList* L){
    if(!tail || !L || LinkedGListLength(L) < 2)
        return ERROR;
    //当表存在且有表尾时继续
    LinkedGLNode temp;
    temp.tag = LIST;
    temp.hp = (*L)->hp->tp;
    LinkedGLNode* p = &temp;
    if(LinkedGListCopy(tail, &p) != OK)//复制表尾
        return ERROR;
    return OK;
}
//插入新表头
Status LinkedGListInsertHead(LinkedGList* L, const LinkedGList* e){
    if(!L || !e || !*L)
        return ERROR;
    LinkedGList p = NULL;
    //直接改指针的话，操作一个表会影响另一个（浅复制）
    //使用深复制
    if(LinkedGListCopy(&p, e) != OK)
        return OVERFLOW;
    LinkedGLNode* node = (LinkedGLNode*)malloc(sizeof(LinkedGLNode));
    if(!node)
        return OVERFLOW;
    node->tag = LIST;
    node->hp = p->hp;
    node->tp = (*L)->hp;
    (*L)->hp = node;
    free(p);
    return OK;
}
//删除原表头
Status LinkedGListDeleteHead(LinkedGList* L, LinkedGList* e){
    if(!L || !e || LinkedGListEmpty(L) != FALSE)//空表情况
        return ERROR;
    if(LinkedGListInit(e) != OK)
        return ERROR;
    //把删除表头赋值给表e
    (*e)->hp = (*L)->hp;
    (*L)->hp = (*L)->hp->tp;
    (*e)->hp->tp = NULL;
    return OK;
}

//遍历广义表
Status LinkedGListTraverse(LinkedGList* L, Status (*visit)(AtomType*)){
    if(!L)
		return ERROR;
	if(!*L)
		return OK;
	if((*L)->tag == ATOM)
		printf("%c ", (*L)->atom);
	else{
		LinkedGListTraverse(&((*L)->hp), visit);
	}
	LinkedGListTraverse(&((*L)->tp), visit);
	return OK;
}
//简单打印
Status LinkedGListVisit(AtomType* a){
    if(!a)
        return ERROR;
    printf("%c ", *a);
    return OK;
}

//由字符串创建广义表
//server方法在StaticStr.h里
Status LinkedGListCreate(LinkedGList* L, StaticStr* S){
    if(!L || !S || LinkedGListInit(L) != OK)//先释放L原来空间
        return ERROR;
    //当L为空表时不需要子函数
    StaticStr* emp = NULL;
    StaticStrInit(&emp);
    StaticStrAssign(emp, "()");
    if(StaticStrCompare(S, emp) == 0){
        (*L)->tag = LIST;
		(*L)->hp = (*L)->tp = NULL;
		return OK;
    }
    return _LinkedGListCreate(&((*L)->hp), S);
}
//递归创建结点子函数
Status _LinkedGListCreate(LinkedGList* L, StaticStr* S){
	*L = (LinkedGLNode*)malloc(sizeof(LinkedGLNode));
	if(!*L)
		return OVERFLOW;

	StaticStr* emp = NULL;
    StaticStrInit(&emp);
    StaticStrAssign(emp, "()");
    if(StaticStrCompare(S, emp) == 0){
        (*L)->tag = LIST;
		(*L)->hp = (*L)->tp = NULL;
    }
	else if(StaticStrLength(S) == 1){
        (*L)->tag = ATOM;
        StaticStrGetChar(S, 1, &((*L)->atom));
        (*L)->tp = NULL;
    }
	else{
        StaticStr* sub = NULL, *hsub = NULL;
        StaticStrInit(&sub);
        StaticStrInit(&hsub);
        StaticStrSubStr(sub, S, 2, StaticStrLength(S) - 2);//剥去外层()
		LinkedGList p = *L, q;
		do{
            q = p;
			StaticStrSever(sub, hsub);
			//StaticStrPrint(sub);
			if(StaticStrLength(hsub) == 1){//表头是单一元素
                p->tag = ATOM;
                StaticStrGetChar(hsub, 1, &p->atom);
			}
			else{//表头是列表
                p->tag = LIST;
                _LinkedGListCreate(&p->hp, hsub);
			}
            if(StaticStrEmpty(sub) == FALSE){
                p = (LinkedGLNode*)malloc(sizeof(LinkedGLNode));
                if(!p)
                    return OVERFLOW;
                q->tp = p;
            }
		}while(StaticStrEmpty(sub) == FALSE);
		q->tp = NULL;
	}
	return OK;
}
