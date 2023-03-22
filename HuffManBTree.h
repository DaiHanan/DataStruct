#ifndef HUFFMANBTREE_H_INCLUDED
#define HUFFMANBTREE_H_INCLUDED

#include "MyDefinition.h"
#include <string.h> //strcpy

// 功　能：实现哈夫曼树和哈夫曼编码
// 设计者：李钰林
// 版本号：2018-10-16

#define HTMAX 10    //树中叶子结点的最大个数

typedef struct _HTNode{
    unsigned int weight;        //结点权重，只有正数
    unsigned int parent;        //双亲结点的下标
    unsigned int left, right;   //左右孩子结点的下标
}HTNode;

typedef struct _HTCode{
    char data;                  //待编码的字符
    unsigned int weight;        //字符权重
    char code[HTMAX];               //字符编码
}HTCode;

//初始化待编码的字符
Status HTInitCode(HTCode hc[], int* n);
//用数组初始化待编码的字符
Status HTInitCodeByNums(HTCode hc[], char chars[], int weights[], int size);
//获得[1,k]中parent == 0 且权重最小的两个结点，返回下标
Status HTSelect(HTNode hn[], int k, int* s1, int* s2);
//构造哈夫曼树，并求出字符编码
Status HTCreate(HTNode hn[], HTCode hc[], int n);

#endif // HUFFMANBTREE_H_INCLUDED
