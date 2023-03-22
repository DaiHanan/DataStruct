#include "DynamicStr.h"

//初始化传入的动态串（创建空串）
Status DynamicStrInit(DynamicStr** str){
    if(!str)
        return ERROR;
    DynamicStrDestroy(*str);//先释放*str所有空间
    *str = (DynamicStr*)malloc(sizeof(DynamicStr)); //动态分配内存
    if(!*str)
        return OVERFLOW;
    (*str)->length = 0;//初始化长度
    (*str)->ch = (char*)malloc(sizeof(char));//内容为空时分配一个char
    if(!(*str)->ch)
        return OVERFLOW;
    return OK;
}
//判断传入的动态串是否为空串
Status DynamicStrEmpty(const DynamicStr* str){
    if(!str || !str->ch || str->length < 0)
        return ERROR;
    return str->length == 0 ? TRUE  : FALSE;
}
//生成一个值为字符串chs的动态串
Status DynamicStrAssign(DynamicStr* str, char chs[]){
    if(DynamicStrEmpty(str) == ERROR || !chs)
        return ERROR;
    int len = 0;
    while(chs[len++]);//获得chs长度
    len--;//因为while中len多加了一次
    str->ch = (char*)realloc(str->ch, sizeof(char) * len);
    if(!str->ch)
        return OVERFLOW;
    for(int i = 0; i < len; i++)//循环分配
        str->ch[i] = chs[i];
    str->length = len;
    return OK;
}
//拷贝动态串
Status DynamicStrCopy(DynamicStr* str, const DynamicStr* src){
    if(DynamicStrEmpty(str) == ERROR || DynamicStrEmpty(src) == ERROR)
        return ERROR;
    if(src->length != str->length)//动态改变数组大小
        str->ch = (char*)realloc(str->ch, sizeof(char) * src->length);
    if(!str->ch)
        return OVERFLOW;
    for(int i = 0; i < src->length; i++)//循环分配
        str->ch[i] = src->ch[i];
    str->length = src->length;//改变长度
    return OK;
}
//将动态串清空
Status DynamicStrClear(DynamicStr* str){
    if(DynamicStrEmpty(str) == ERROR)
        return ERROR;
    str->ch = (char*)realloc(str->ch, sizeof(char));//内存变为一个char
    if(!str->ch)
        return OVERFLOW;
    str->length = 0;
    return OK;
}
//删除传入的动态串
Status DynamicStrDestroy(DynamicStr* str){
    if(DynamicStrEmpty(str) == ERROR)
        return ERROR;
    free(str->ch);//释放内存
    free(str);
    //str变为野指针，需手动NULL
    return OK;
}
//连接动态串str1和str2，用res返回
Status DynamicStrConcat(DynamicStr* res, const DynamicStr* str1, const DynamicStr* str2){
    if(DynamicStrEmpty(res) == ERROR ||
       DynamicStrEmpty(str1) == ERROR ||
       DynamicStrEmpty(str2) == ERROR)
        return ERROR;
    if(res->length != str1->length + str2->length)//动态改变大小
        res->ch = (char*)realloc(res->ch, sizeof(char) * (str1->length + str2->length));
    if(!res->ch)
        return OVERFLOW;
    //两个循环复制内容
    for(int i = 0; i < str1->length; i++)
        res->ch[i] = str1->ch[i];
    for(int i = 0; i < str2->length; i++)
        res->ch[i + str1->length] = str2->ch[i];
    //改变长度
    res->length = str1->length + str2->length;
    return OK;
}
//获得动态串长度
int DynamicStrLength(const DynamicStr* str){
    if(DynamicStrEmpty(str) == ERROR)
        return ERROR;
    return str->length;
}
//比较传入的两个动态串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int DynamicStrCompare(const DynamicStr* str1, const DynamicStr* str2){
    int i = 0;
    while(str1->length > i && str2->length > i){//先比较相同位置元素的ASCII码大小
        if(str1->ch[i] != str2->ch[i])
            return str1->ch[i] - str2->ch[i];
        i++;
    }
    return str1->length - str2->length;//再比较元素个数
}
//返回动态串中pos位置开始长为len的子串
Status DynamicStrSubStr(DynamicStr* sub, const DynamicStr* src, int pos, int len){
    if(DynamicStrEmpty(sub) == ERROR ||
       DynamicStrEmpty(src) == ERROR ||
       pos + len - 1 > src->length ||
       pos < 1 || len < 0)
        return ERROR;
    //当两个动态串不为空且pos和len恰当时继续
    if(sub->length != len)//动态改变大小
        sub->ch = (char*)realloc(sub->ch, sizeof(char) * len);
    if(!sub->ch)
        return OVERFLOW;
    int j = 0;
    for(int i = pos - 1; i < pos + len - 1; i++){
        sub->ch[j++] = src->ch[i];
    }
    sub->length = j;
    return OK;
}
//在动态串str1中pos位置插入另一静态串str2
Status DynamicStrInsert(DynamicStr* str1, const DynamicStr* str2, int pos){
    if(DynamicStrEmpty(str1) == ERROR ||
       DynamicStrEmpty(str2) == ERROR ||
       pos < 1 || pos > str1->length + 1)
        return ERROR;
    //当两个动态串不为空且pos和len恰当时继续
    if(str2->length == 0)
        return OK;//长度为0不需要继续
    str1->ch = (char*)realloc(str1->ch, sizeof(char) * (str1->length + str2->length));
    if(!str1->ch)
        return OVERFLOW;
    for(int i = str1->length - 1; i >= pos - 1; i--){
        //为插入动态串提供位置
        str1->ch[i + str2->length] = str1->ch[i];
    }
    for(int i = 0; i < str2->length; i++){
        str1->ch[i + pos - 1] = str2->ch[i];
    }
    str1->length += str2->length;
    return OK;
}
//在动态串str中删除pos位置开始长len的子串
Status DynamicStrDelete(DynamicStr* str, int pos, int len){
    if(DynamicStrEmpty(str) == ERROR ||
       pos < 1 || len < 0 || pos + len - 1 > str->length)
        return ERROR;
    if(!len)
        return OK;//长度为0不需要继续
    for(int i = 0; i < str->length - pos + 1; i++){
        str->ch[pos - 1 + i] = str->ch[pos + i + len - 1];
    }
    str->ch = (char*)realloc(str->ch, sizeof(char) * (str->length - len));
    if(!str->ch)
        return OVERFLOW;
    str->length -= len;
    return OK;
}

//从pos位置开始找动态串src中子串str的位置未找到返回0; （kmp算法）
int DynamicStrSubPos(const DynamicStr* src, const DynamicStr* str, int pos){
    if(DynamicStrEmpty(src) == ERROR ||
       DynamicStrEmpty(str) == ERROR ||
       pos < 1 || pos > src->length)
        return ERROR;
    int i = pos - 1;
    int j = 0;
    //next大小不确定，动态分配
    int* next = (int*)malloc(sizeof(int) * str->length);
    if(!next)
        return OVERFLOW;
    Dynamic_get_next(str, next);
    while(i < src->length && j < str->length){
        if(j == -1 || src->ch[i] == str->ch[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    free(next);
    return j == str->length ? i - str->length + 1 : 0;//返回位置要加一

}
//辅助kmp算法的方法
void Dynamic_get_next(DynamicStr* str, int next[]){
    int i = 0;
    int j = -1;
    next[0] = -1;
    while(i < str->length){
        if(j == -1 || str->ch[i] == str->ch[j]){
            i++;
            j++;
            next[i] = j;
        }
        else{
            j = next[j];
        }
    }
}

//用str2替换src中所有和str1相等的子串
Status DynamicStrReplace(DynamicStr* src, const DynamicStr* str1, const DynamicStr* str2){
    if(DynamicStrEmpty(src) == ERROR ||
       DynamicStrEmpty(str1) == ERROR ||
       DynamicStrEmpty(str2) == ERROR)
        return ERROR;
    int pos = 1;
    while((pos = DynamicStrSubPos(src, str1, pos)) != 0){
        if(DynamicStrDelete(src, pos, str1->length) == ERROR)
            return ERROR;
        if(DynamicStrInsert(src, str2, pos) == ERROR)
            return ERROR;
        pos += str2->length;
    }
    return OK;
}

//打印动态串
Status DynamicStrPrint(const DynamicStr* str){
    if(DynamicStrEmpty(str) == ERROR)
        return ERROR;
    if(str->length == 0){
        printf("动态串为空！\n");
        return OK;
    }
    for(int i = 0; i < str->length; i++){
        printf("%c", str->ch[i]);
    }
    printf("\n");
    return OK;
}
