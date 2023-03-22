#ifndef MYDEFINITION_H_INCLUDED
#define MYDEFINITION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define OK 1     //Status用，成功
#define ERROR -1  //Status用，失败
#define TRUE 1   //Status用，确定
#define FALSE 0  //Status用，否定
#define OVERFLOW -2 //Status用，申请内存失败

typedef int Status;     //状态码
typedef int ElemType;   //数据类型（用int代替）

#endif // MYDEFINITION_H_INCLUDED
