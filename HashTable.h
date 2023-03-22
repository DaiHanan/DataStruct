#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现各种排序（顺序）
// 设计者：李钰林
// 版本号：2018-12-7

#define HASHSIZE 12         //哈希表数组长度
#define NULLKEY -1          //空位

typedef struct _hashTable{
    ElemType data[HASHSIZE];//数据数组
    int count;              //当前元素个数
}HashTable;

//初始化
Status HashTableInit(HashTable* h);
//插入
Status HashTableInsert(HashTable* h, ElemType key);
//查找(地址)
Status HashTableFind(HashTable h, ElemType key, int* addr);
//Hash函数
int Hash(ElemType key);
//Hash函数备用
int Hash1(ElemType key);


#endif // HASHTABLE_H_INCLUDED
