#include "Array.h"

//初始化数组（创建数组）
Status ArrayInit(Array** A, int dim, ...){
    if(!A)
        return ERROR;
    ArrayDestroy(*A);//如果*A原本存在，先释放原先空间
    *A = (Array*)malloc(sizeof(Array));
    if(!*A)
        return OVERFLOW;
    (*A)->dim = dim;//赋值维度个数
    (*A)->bounds = (int*)malloc(sizeof(int) * dim);
    if(!(*A)->bounds)
        return OVERFLOW;
    va_list ap;
    va_start(ap, dim);
    int size = 1;//数组元素个数
    for(int i = 0; i < dim; i++){
        (*A)->bounds[i] = va_arg(ap, int);//赋值每个维度大小
        if((*A)->bounds[i] <= 0)
            return ERROR;
        size *= (*A)->bounds[i];
    }
    va_end(ap);
    (*A)->base = (ElemType*)malloc(sizeof(ElemType) * size);
    if(!(*A)->base)
        return OVERFLOW;
    (*A)->constants = (int*)malloc(sizeof(int) * dim);
    (*A)->constants[dim - 1] = 1;
    for(int i = dim - 2; i >= 0; i--){
        //初始化权重
        (*A)->constants[i] = (*A)->constants[i + 1] * (*A)->bounds[i + 1];
    }
    //初始化base空间
    for(int i = 0; i < size; i++)
        (*A)->base[i] = 0;
    return OK;
}
//销毁数组
Status ArrayDestroy(Array* A){
    if(!A)
        return ERROR;
    if(A->base)
        free(A->base);
    if(A->bounds)
        free(A->bounds);
    if(A->constants)
        free(A->constants);
    free(A);
    return OK;
}
//复制数组（强制改变数组大小）
Status ArrayCopy(Array* A, const Array* src){
    if(!src || !A)
        return ERROR;
    //需要计算src中base大小
    int size = 1;
    int dim = src->dim;
    for(int i = 0; i < dim; i++){
        size *= src->bounds[i];
    }
    //因事先不确定A的维数，不能调用init函数
    A->base = (ElemType*)realloc(A->base, sizeof(ElemType) * size);
    if(!A->base)
        return OVERFLOW;
    for(int i = 0; i < size; i++){
        A->base[i] = src->base[i];
    }
    A->bounds = (int*)realloc(A->bounds, sizeof(int) * dim);
    A->constants = (int*)realloc(A->constants, sizeof(int) * dim);
    if(!A->bounds || !A->constants)
        return OVERFLOW;
    for(int i = 0; i < dim; i++){
        A->bounds[i] = src->bounds[i];
        A->constants[i] = src->constants[i];
    }
    A->dim = dim;
    return OK;
}

//定位元素位置（辅助函数）
Status ArrayLocate(const Array* A, va_list ap, int* off){
    *off = 0;
    int idx;
    for(int i = 0; i < A->dim; i++){
        idx = va_arg(ap, int);
        if(idx < 0 || idx >= A->bounds[i])
            return ERROR;
        *off += idx * A->constants[i];
    }
    return OK;
}
//赋值指定位置的元素
Status ArrayAssign(Array* A, ElemType e, ...){
    if(!A)
        return ERROR;
    va_list ap;
    va_start(ap, e);
    int off;
    if(ArrayLocate(A, ap, &off) == ERROR)
        return ERROR;
    va_end(ap);
    A->base[off] = e;
    return OK;
}
//取出指定位置的元素
Status ArrayValue(const Array* A, ElemType* e, ...){
    if(!A ||  !e)
        return ERROR;
    va_list ap;
    va_start(ap, e);
    int off;
    if(ArrayLocate(A, ap, &off) == ERROR)
        return ERROR;
    va_end(ap);
    *e = A->base[off];
    return OK;
}
