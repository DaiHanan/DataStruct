#ifndef LINKEDSTR_H_INCLUDED
#define LINKEDSTR_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现块链串
// 设计者：李钰林
// 版本号：2018-10-05

#define BLOCK_SIZE 5    //自定义块的大小，为测试需要改小为5

typedef struct _block{
    char ch[BLOCK_SIZE];
    struct _block* next;
}Block;

typedef struct _linkedStr{
    Block* head;        //块链串的头指针
    Block* tail;        //块链串的尾指针
    int length;         //块链串的当前长度
}LinkedStr;

//初始化传入的块链串（创建空串）
Status LinkedStrInit(LinkedStr** str);
//判断传入的块链串是否为空串
Status LinkedStrEmpty(const LinkedStr* str);
//生成一个值为字符串chs的块链串
Status LinkedStrAssign(LinkedStr* str, char chs[]);
//拷贝块链串
Status LinkedStrCopy(LinkedStr* str, const LinkedStr* src);
//将块链串清空
Status LinkedStrClear(LinkedStr* str);
//删除传入的块链串
Status LinkedStrDestroy(LinkedStr* str);
//连接块链串str1和str2，用res返回
Status LinkedStrConcat(LinkedStr* res, const LinkedStr* str1, const LinkedStr* str2);
//获得块链串长度
int LinkedStrLength(const LinkedStr* str);
//比较传入的两个块链串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int LinkedStrCompare(const LinkedStr* str1, const LinkedStr* str2);
//返回块链串中pos位置开始长为len的子串
Status LinkedStrSubStr(LinkedStr* sub, const LinkedStr* src, int pos, int len);
//在块链串str1中pos位置插入另一块链串str2
Status LinkedStrInsert(LinkedStr* str1, const LinkedStr* str2, int pos);
//在块链串str中删除pos位置开始长len的子串
Status LinkedStrDelete(LinkedStr* str, int pos, int len);

//从pos位置开始找静态串src中子串str的位置未找到返回0（非kmp）
int LinkedStrSubPos(const LinkedStr* src, const LinkedStr* str, int pos);

//用str2替换src中所有和str1相等的子串
Status LinkedStrReplace(LinkedStr* src, const LinkedStr* str1, const LinkedStr* str2);

//打印块链串
Status LinkedStrPrint(const LinkedStr* str);


#endif // LINKEDSTR_H_INCLUDED
