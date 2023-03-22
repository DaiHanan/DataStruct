#include "SubGList.h"

//初始化广义表（创建广义表）
Status SubGListInit(SubGList* L){
    if(!L)
       return ERROR;
    //先释放空间
    SubGListDestroy(L);
    *L = NULL;
    return OK;
}
//求广义表的长度
int SubGListLength(SubGList* L){
    if(!L)
        return ERROR;
    if(!*L)
        return 0;
    if((*L)->tag == ATOM)
        return 1;
    int len = 0;
    SubGList p = *L;
    while(p){
        len++;
        if(p->tag == ATOM)
            break;
        p = p->ptr.tp;
    }
    return len;
}
//求广义表的深度
int SubGListDepth(SubGList* L){
    if(!L)
        return ERROR;
    if(!*L)
        return 1;
    if((*L)->tag == ATOM)
        return 0;
    int max, dep;
    SubGList p;
    for(max = 0, p = *L; p; p = p->ptr.tp){
        dep = SubGListDepth(&(p->ptr.hp));
        max = max > dep ? max : dep;
    }
    return max + 1;
}
//销毁广义表
Status SubGListDestroy(SubGList* L){
    if(!L)
        return ERROR;
    if(!*L)
        return OK;
    if((*L)->tag == ATOM)
        free(*L);
    else{
        SubGList* p = (*L)->ptr.hp, q = (*L)->ptr.tp;
        //需要先销毁L并将L置为空
        free(*L);
        *L = NULL;
        if(SubGListDestroy(&p) != OK)
            return ERROR;
        if(SubGListDestroy(&q) != OK)
            return ERROR;
    }
    return OK;
}
//广义表复制
Status SubGListCopy(SubGList* L, const SubGList* src){
    if(!L || !src)
        return ERROR;
    //因为递归所以不能先在开始时销毁（初始化）L的空间
    if(!*src)
        *L = NULL;
    else{
        if((*L = (SubGLNode*)malloc(sizeof(SubGLNode))) == NULL)
            return OVERFLOW;
        (*L)->tag = (*src)->tag;
        if((*src)->tag == ATOM){
            (*L)->atom = (*src)->atom;
        }
        else{
            SubGListCopy(&((*L)->ptr.hp), &((*src)->ptr.hp));
            SubGListCopy(&((*L)->ptr.tp), &((*src)->ptr.tp));
        }
    }
    return OK;
}
//判空
Status SubGListEmpty(SubGList* L){
    if(!L)
        return ERROR;
    return *L ? TRUE : FALSE;
}
//获取表头
Status SubGListGetHead(SubGList* head, const SubGList* L){
    if(!head || !L || !*L)//空表没表头
        return ERROR;
    SubGListDestroy(head);
    if((*L)->tag == ATOM){
        return SubGListCopy(head, L);
    }

    SubGList temp = (*L)->ptr.tp;
    (*L)->ptr.tp = NULL;
    if(SubGListCopy(head, L) != OK)
        return ERROR;
    (*L)->ptr.tp = temp;
    return OK;
}
//获取表尾
Status SubGListGetTail(SubGList* tail, const SubGList* L){
    if(!tail || !L || !*L)//空表没表尾
        return ERROR;
    if((*L)->tag == ATOM)
        return SubGListCopy(tail, L);
    return SubGListCopy(tail, &(*L)->ptr.tp);
}
//插入新表头
Status SubGListInsertHead(SubGList* L, const SubGList* e){
    if(!L || !e)
        return ERROR;
    SubGLNode* node = (SubGLNode*)malloc(sizeof(SubGLNode));
    if(!node)
        return OVERFLOW;
    /*浅复制
    p->tag = LIST;
    p->ptr.tp = *L;
    p->ptr.hp = *e;
    *L = p;
    */
    //深复制
    SubGLNode* p = NULL;
    if(SubGListCopy(&p, e) != OK)
        return OVERFLOW;
    node->tag = LIST;
    node->ptr.tp = *L;
    node->ptr.hp = p;
    *L = node;
    return OK;
}
//删除原表头
Status SubGListDeleteHead(SubGList* L, SubGList* e){
    if(!L || !e || !*L)//空表情况
        return ERROR;
    //把删除表头赋值给表e
    if((*L)->tag == ATOM){
        *e = *L;
        *L = NULL;
    }
    else{
        SubGLNode* p = *L;
        *e = (*L)->ptr.hp;
        *L = (*L)->ptr.tp;
        free(p);
    }
    return OK;
}

//遍历广义表
Status SubGListTraverse(SubGList* L, Status (*visit)(AtomType*)){
    if(!L)
        return ERROR;
    if(*L){
        if((*L)->tag == ATOM)
            visit(&(*L)->atom);
        else{
            SubGListTraverse(&(*L)->ptr.hp, visit);
            SubGListTraverse(&(*L)->ptr.tp, visit);
        }
    }
    return OK;
}
//简单打印
Status SubGListVisit(AtomType* a){
    if(!a)
        return ERROR;
    printf("%c ", *a);
    return OK;
}

//由字符串创建广义表
Status SubGListCreate(SubGList* L, StaticStr* S){
    if(!L || !S)
        return ERROR;
    //因为递归所以不能先在开始时销毁（初始化）L的空间

    StaticStr* emp = NULL;
    StaticStrInit(&emp);
    StaticStrAssign(emp, "()");
    if(StaticStrCompare(S, emp) == 0){
        *L = NULL;
        return OK;
    }

    *L = (SubGLNode*)malloc(sizeof(SubGLNode));
    if(!*L)
        return OVERFLOW;
    if(StaticStrLength(S) == 1){
        (*L)->tag = ATOM;
        StaticStrGetChar(S, 1, &((*L)->atom));
        return OK;
    }
    (*L)->tag = LIST;
    SubGList p = *L, q;
    StaticStr* sub = NULL, *hsub = NULL;
    StaticStrInit(&sub);
    StaticStrInit(&hsub);
    StaticStrSubStr(sub, S, 2, StaticStrLength(S) - 2);
    do{
        StaticStrSever(sub, hsub);
        SubGListCreate(&p->ptr.hp, hsub);
        q = p;
        if(StaticStrEmpty(sub) == FALSE){
            p = (SubGLNode*)malloc(sizeof(SubGLNode));
            if(!p)
                return OVERFLOW;
            p->tag = LIST;
            q->ptr.tp = p;
        }
    }while(StaticStrEmpty(sub) == FALSE);
    q->ptr.tp = NULL;
    return OK;
}
