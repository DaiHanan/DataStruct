#ifndef STATICSTR_H_INCLUDED
#define STATICSTR_H_INCLUDED

#include "MyDefinition.h"


// 功　能：实现静态串
// 设计者：李钰林
// 版本号：2018-10-04

#define MAXSIZE 100 //假设只能装100个元素

typedef struct _staticStr{
    char ch[MAXSIZE];   //静态串的内容数组
    int length;         //静态串的当前长度
}StaticStr;

//初始化传入的静态串（创建空串）
Status StaticStrInit(StaticStr** str);
//判断传入的静态串是否为空串
Status StaticStrEmpty(const StaticStr* str);
//生成一个值为字符串chs的静态串
Status StaticStrAssign(StaticStr* str, char chs[]);
//拷贝静态串
Status StaticStrCopy(StaticStr* str, const StaticStr* src);
//将静态串清空
Status StaticStrClear(StaticStr* str);
//删除传入的静态串
Status StaticStrDestroy(StaticStr* str);
//连接静态串str1和str2，用res返回
Status StaticStrConcat(StaticStr* res, const StaticStr* str1, const StaticStr* str2);
//获得静态串长度
int StaticStrLength(const StaticStr* str);
//比较传入的两个静态串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int StaticStrCompare(const StaticStr* str1, const StaticStr* str2);
//返回静态串中pos位置开始长为len的子串
Status StaticStrSubStr(StaticStr* sub, const StaticStr* src, int pos, int len);
//在静态串str1中pos位置插入另一静态串str2
Status StaticStrInsert(StaticStr* str1, const StaticStr* str2, int pos);
//在静态串str中删除pos位置开始长len的子串
Status StaticStrDelete(StaticStr* str, int pos, int len);

//从pos位置开始找静态串src中子串str的位置未找到返回0; （kmp算法）
int StaticStrSubPos(const StaticStr* src, const StaticStr* str, int pos);
//辅助kmp算法的方法
void StaticStrGetNext(StaticStr* str, int next[]);

//用str2替换src中所有和str1相等的子串
Status StaticStrReplace(StaticStr* src, const StaticStr* str1, const StaticStr* str2);

//SubGList里用
//将非空串分为 ','前后两个部分hstr为 ','之前的部分
Status StaticStrSever(StaticStr* str, StaticStr* hstr);

//打印静态串
Status StaticStrPrint(const StaticStr* str);
//返回pos位置的char类型元素
Status StaticStrGetChar(const StaticStr* str, int pos, char* ch);

#endif // STATICSTR_H_INCLUDED
