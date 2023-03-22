#include "RLSMatrix.h"

//初始化矩阵（创建矩阵）
Status RLSMatrixInit(RLSMatrix** M, int line, int col){
    if(!M)
        return ERROR;
    TSMatrixDestroy(*M);
    *M = (RLSMatrix*)malloc(sizeof(RLSMatrix));
    if(!*M)
        return OVERFLOW;
    (*M)->line = line;
    (*M)->col = col;
    (*M)->count = 0;
    for(int i = 0; i < line; i++){
        (*M)->rIdx[i] = col;
    }
    return OK;
}
//销毁矩阵
Status RLSMatrixDestroy(RLSMatrix* M){
    if(!M)
        return ERROR;
    free(M);
    return OK;
}
//复制矩阵（强制改变矩阵大小）
Status RLSMatrixCopy(RLSMatrix* M, const RLSMatrix* src){
    if(!M || !src)
        return ERROR;
    M->col = src->col;
    M->line = src->line;
    M->count = src->count;
    for(int i = 0; i < src->count; i++){
        M->data[i] = src->data[i];
    }
    for(int i = 0; i < src->line; i++){
        M->rIdx[i] =  src->rIdx[i];
    }
    return OK;
}
//赋值指定位置（下标）的元素
Status RLSMatrixAssign(RLSMatrix* M, ElemType e, int line, int col){
    if(!M || line < 0 || col < 0 || line >= M->line || col >= M->col)
        return ERROR;
    ElemType temp;
    RLSMatrixValue(M, &temp, line, col);//先取出被替换的元素
    if(temp != 0 && e != 0){//改变非零元
        for(int i = 0; i < M->count; i++){
            if(M->data[i].i == line && M->data[i].j == col){
                M->data[i].e = e;
                return OK;
            }
        }
        return ERROR;
    }
    else if(temp == 0 && e != 0){//增加非零元
        //新增非零元，为了打印方便，排序插入
        int i = 0;
        for(; i < M->count; i++){//找到插入点
            if(line <= M->data[i].i && col <= M->data[i].j)
                break;
        }
        for(int j = M->count - 1; j >= i; j--){//腾出空间
            M->data[j + 1] = M->data[j];
        }
        M->data[i].i = line;
        M->data[i].j = col;
        M->data[i].e = e;
        M->count++;//更新非零元数量
        //修改rIdx
        M->rIdx[line] = M->rIdx[line] > col ? col : M->rIdx[line];
        return OK;
    }
    else if(temp != 0 && e == 0){//删除非零元
        int i = 0;
        for(; i < M->count; i++){
            if(M->data[i].i == line && M->data[i].j == col)
                break;
        }
        for(; i < M->count - 1; i++){
            M->data[i] = M->data[i + 1];
        }
        M->count--;//更新非零元数量
        //为打印方便当count == 0 时修改data[0]
        if(M->count == 0)
            M->data[0].i = -1;
        //修改rIdx
        if(M->rIdx[line] == col){
            for(int i = 0; i < M->count; i++){
                if(M->data[i].i == line && M->data[i].j > col){
                    M->rIdx[line] = M->data[i].j;
                    break;
                }
                else
                    M->rIdx[line] = M->col;
            }
        }
        return OK;
    }
    //还有情况都为0，不需要处理
    return OK;
}
//取出指定位置（下标）的元素
Status RLSMatrixValue(const RLSMatrix* M, ElemType* e, int line, int col){
    if(!M || line < 0 || col < 0 || line >= M->line || col >= M->col)
        return ERROR;
    for(int i = 0; i < M->count; i++){//先在非零元中找
        if(M->data[i].i == line && M->data[i].j == col){
            *e = M->data[i].e;
            return OK;
        }
    }
    //没找到说明是零元
    *e = 0;
    return OK;
}
//简单打印矩阵
Status RLSMatrixPrint(const RLSMatrix* M){
    if(!M)
        return ERROR;
    int k = 0;//非零元下标
    for(int i = 0; i < M->line; i++){
        for(int j = 0; j < M->col; j++){
            if(k < M->count && M->data[k].i == i && M->data[k].j == j){
                printf("%-3d", M->data[k++].e);
            }
            else
                printf("0  ");
        }
        printf("\n");
    }
    return OK;
}

//获得line（下标）第一个非零元的下标，没有返回-1
Status RLSMatrixGetLineFirstElem(const RLSMatrix* M, int line,int* col){
    if(!M || line < 1 || line > M->line)
        return ERROR;
    *col = M->rIdx[line - 1] == M->col ? -1 : M->rIdx[line - 1];
    return OK;
}
