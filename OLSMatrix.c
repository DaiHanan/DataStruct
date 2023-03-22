#include "OLSMatrix.h"

//初始化矩阵（创建矩阵）
Status OLSMatrixInit(OLSMatrix** M, int line, int col){
    if(!M)
        return ERROR;
    OLSMatrixDestroy(*M);
    //动态分配内存
    if((*M = (OLSMatrix*)malloc(sizeof(OLSMatrix))) == NULL)
        return OVERFLOW;
    if(((*M)->rhead = (OLNode**)malloc(sizeof(OLNode*) * line)) == NULL)
        return OVERFLOW;
    if(((*M)->chead = (OLNode**)malloc(sizeof(OLNode*) * col)) == NULL)
        return OVERFLOW;
    //初始化
    for(int i = 0; i < line; i++){
        (*M)->rhead[i] = NULL;
    }
    for(int i = 0; i < col; i++){
        (*M)->chead[i] = NULL;
    }
    (*M)->line = line;
    (*M)->col = col;
    (*M)->count = 0;
    return OK;
}
//销毁矩阵
Status OLSMatrixDestroy(OLSMatrix* M){
    if(!M)
        return ERROR;
    //因为行列指针都链接了所有的节点，只需遍历一个
    for(int i = 0; i < M->line; i++){
        OLNode* p = M->rhead[i], * q;
        while(p){
            q = p->right;
            free(p);
            p = q;
        }
    }
    //释放所有申请的内存
    free(M->chead);
    free(M->rhead);
    free(M);
    return OK;
}
//复制矩阵（强制改变矩阵大小）
Status OLSMatrixCopy(OLSMatrix* M, const OLSMatrix* src){
    if(!M || !src)
        return ERROR;

    OLSMatrix m = *M;
    OLSMatrix* pm = &m;
    //初始化M
    //不清楚为什么不能直接传M，但是这样也不会泄露空间
    if(OLSMatrixInit(&pm, src->line, src->col) != OK)
        return OVERFLOW;
    *M = *pm;

    for(int i = 0; i < src->line; i++){
        OLNode* p = src->rhead[i];
        while(p){
            if(OLSMatrixAssign(M, p->e, p->i, p->j) != OK)
                return ERROR;
            p = p->right;
        }
    }
    return OK;
}
//赋值指定位置（下标）的元素
Status OLSMatrixAssign(OLSMatrix* M, ElemType e, int line, int col){
    if(!M || line < 0 || col < 0 || line >= M->line || col >= M->col)
        return ERROR;
    ElemType temp;
    //先找到要替换的元素，看是否为零元
    if(OLSMatrixValue(M, &temp, line, col) == ERROR)
        return ERROR;
    if(temp && e){//替换非零元
        OLNode* p = M->rhead[line];
        while(p){
            if(p->e == temp){
                p->e = e;
                return OK;
            }
            p = p->right;
        }
        return ERROR;
    }
    else if(!temp && e){//增加非零元
        OLNode* newNode = (OLNode*)malloc(sizeof(OLNode));
        if(newNode == NULL)
            return OVERFLOW;
        newNode->i = line;
        newNode->j = col;
        newNode->e = e;

        //初始化right指针
        OLNode* p = M->rhead[line];
        if(!p){
            M->rhead[line] = newNode;
            newNode->right = NULL;
        }
        else{
            //找到插入位置
            if(p->j < col){
                while(p->right){
                    if(p->right->j > col)
                        break;
                    p = p->right;
                }
            }
            newNode->right = p->right;
            p->right = newNode;
        }

        //初始化down指针
        p = M->chead[col];
        if(!p){
            M->chead[col] = newNode;
            newNode->down = NULL;
        }
        else{
            if(p->i < line){
                while(p->down){
                    if(p->down->i > line)
                        break;
                    p = p->down;
                }
            }
            newNode->down = p->down;
            p->down = newNode;
        }
        M->count++;
        return OK;
    }
    else if(temp && !e){//删除非零元
        OLNode* p = M->rhead[line];
        OLNode* q = M->chead[line];
        //需要q、p同时指向删除元素前一个元素才能成功删除
        if(p->e != temp){
            while(p->right){
                if(p->right->e == temp)
                    break;
                p = p->right;
            }
        }
        if(q->e != temp){
            while(q){
                if(q->down->e == temp)
                    break;
                q = q->down;
            }
        }
        if(p->right != q->down)
            return ERROR;
        OLNode* delNode = p->right;
        p->right = p->right->right;
        q->down = q->down->down;
        free(delNode);
        M->count--;
        return OK;
    }
    //还有零元换零元，不需要操作
    return OK;
}
//取出指定位置（下标）的元素
Status OLSMatrixValue(const OLSMatrix* M, ElemType* e, int line, int col){
    if(!M || line < 0 || col < 0 || line >= M->line || col >= M->col)
        return ERROR;
    OLNode* p = M->rhead[line];
    while(p){
        if(p->j == col){
            *e = p->e;
            return OK;
        }
        p = p->right;
    }
    //没找到说明是零元
    *e = 0;
    return OK;
}
//简单打印矩阵
Status OLSMatrixPrint(const OLSMatrix* M){
    if(!M || M->count < 0)
        return ERROR;
    for(int i = 0; i < M->line; i++){
        OLNode* p = M->rhead[i];
        for(int j = 0; j < M->col; j++){
            if(p && p->j == j){
                printf("%-3d ", p->e);
                p = p->right;
            }
            else
                printf("0    ");
        }
        printf("\n");
    }
    printf("\n");
    return OK;
}
