#ifndef DYNAMICSTR_H_INCLUDED
#define DYNAMICSTR_H_INCLUDED

#include "MyDefinition.h"

// 功　能：实现动态串
// 设计者：李钰林
// 版本号：2018-10-05

typedef struct _dynamicStr{
    char* ch;           //动态串的内容指针，动态分配大小
    int length;         //动态串的当前长度
}DynamicStr;

//初始化传入的动态串（创建空串）
Status DynamicStrInit(DynamicStr** str);
//判断传入的动态串是否为空串
Status DynamicStrEmpty(const DynamicStr* str);
//生成一个值为字符串chs的动态串
Status DynamicStrAssign(DynamicStr* str, char chs[]);
//拷贝动态串
Status DynamicStrCopy(DynamicStr* str, const DynamicStr* src);
//将动态串清空
Status DynamicStrClear(DynamicStr* str);
//删除传入的动态串
Status DynamicStrDestroy(DynamicStr* str);
//连接动态串str1和str2，用res返回
Status DynamicStrConcat(DynamicStr* res, const DynamicStr* str1, const DynamicStr* str2);
//获得动态串长度
int DynamicStrLength(const DynamicStr* str);
//比较传入的两个动态串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int DynamicStrCompare(const DynamicStr* str1, const DynamicStr* str2);
//返回动态串中pos位置开始长为len的子串
Status DynamicStrSubStr(DynamicStr* sub, const DynamicStr* src, int pos, int len);
//在动态串str1中pos位置插入另一静态串str2
Status DynamicStrInsert(DynamicStr* str1, const DynamicStr* str2, int pos);
//在动态串str中删除pos位置开始长len的子串
Status DynamicStrDelete(DynamicStr* str, int pos, int len);

//从pos位置开始找动态串src中子串str的位置未找到返回0; （kmp算法）
int DynamicStrSubPos(const DynamicStr* src, const DynamicStr* str, int pos);
//辅助kmp算法的方法
void get_next(DynamicStr* str, int next[]);

//用str2替换src中所有和str1相等的子串
Status DynamicStrReplace(DynamicStr* src, const DynamicStr* str1, const DynamicStr* str2);

//打印动态串
Status DynamicStrPrint(const DynamicStr* str);

#endif // DYNAMICSTR_H_INCLUDED
