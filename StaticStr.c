#include "StaticStr.h"

//初始化传入的静态串（创建空串）
Status StaticStrInit(StaticStr** str){
    if(!str)
        return ERROR;
    if(*str)
        free(*str);
    *str = (StaticStr*)malloc(sizeof(StaticStr));
    (*str)->length = 0;
    return OK;
}
//判断传入的静态串是否为空串
Status StaticStrEmpty(const StaticStr* str){
    if(!str || str->length < 0)
        return ERROR;
    return str->length == 0 ? TRUE : FALSE;
}
//生成一个值为字符串chs的静态串，截断式
Status StaticStrAssign(StaticStr* str, char chs[]){
    if(!str || !chs)
        return ERROR;
    int length = 0;
    while(chs[length++] != '\0');
    length--;//因为while中length多加了1
    length == length < MAXSIZE ? length : MAXSIZE;
    for(int i = 0; i < length; i++){
        str->ch[i] = chs[i];
    }
    str->length = length;
    return OK;
}
//拷贝顺序栈
Status StaticStrCopy(StaticStr* str, const StaticStr* src){
    if(!str || !src)
        return ERROR;
    str->length = src->length;
    for(int i = 0; i < src->length; i++){
        str->ch[i] = src->ch[i];
    }
    return OK;
}
//将静态串清空
Status StaticStrClear(StaticStr* str){
    if(!str)
        return ERROR;
    str->length = 0;
    return OK;
}
//删除传入的静态串
Status StaticStrDestroy(StaticStr* str){
    if(!str)
        return ERROR;
    free(str);
    return OK;
}
//连接静态串str1和str2，用res返回
Status StaticStrConcat(StaticStr* res, const StaticStr* str1, const StaticStr* str2){
    if(!res || !str1 || !str2)
        return ERROR;
    StaticStrCopy(res, str1);//先把str1复制给res
    //当res中还有位置且str2中还有元素时复制
    int i = 0;
    while(res->length < MAXSIZE && str2->ch[i] != '\0'){
        res->ch[res->length++] =  str2->ch[i++];
    }
    return OK;
}
//获得顺序栈长度
int StaticStrLength(const StaticStr* str){
    if(!str)
        return ERROR;
    return str->length;
}
//比较传入的两个静态串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int StaticStrCompare(const StaticStr* str1, const StaticStr* str2){
    int i = 0;
    while(str1->length > i && str2->length > i){//先比较相同位置元素的ASCII码大小
        if(str1->ch[i] != str2->ch[i])
            return str1->ch[i] - str2->ch[i];
        i++;
    }
    return str1->length - str2->length;//再比较元素个数
}
//返回静态串中pos位置开始长为len的子串
Status StaticStrSubStr(StaticStr* sub, const StaticStr* src, int pos, int len){
    if(!src || !sub || pos + len - 1 > src->length || pos < 1)
        return ERROR;
    //当两个静态串不为空且pos和len恰当时继续
    int j = 0;
    for(int i = pos - 1; i < pos + len - 1; i++){
        sub->ch[j++] = src->ch[i];
    }
    sub->length = j;
    return OK;
}
//在静态串str1中pos位置插入另一静态串str2
Status StaticStrInsert(StaticStr* str1, const StaticStr* str2, int pos){
    if(!str1 || !str2 ||
       str1->length + str2->length > MAXSIZE ||
       pos < 1 || pos > str1->length + 1)
        return ERROR;
    for(int i = str1->length - 1; i >= pos - 1; i--){
        //为插入静态串提供位置
        str1->ch[i + str2->length] = str1->ch[i];
    }
    for(int i = 0; i < str2->length; i++){
        str1->ch[i + pos - 1] = str2->ch[i];
    }
    str1->length += str2->length;
    return OK;
}
//在静态串str中删除pos位置开始长len的子串
Status StaticStrDelete(StaticStr* str, int pos, int len){
    if(!str || pos < 1 || len < 0 || pos + len - 1 > str->length)
        return ERROR;
    for(int i = 0; i < str->length - pos + 1; i++){
        str->ch[pos - 1 + i] = str->ch[pos + i + len - 1];
    }
    str->length -= len;
    return OK;
}

//从pos位置开始找静态串src中子串str的位置未找到返回0; （kmp算法）
int StaticStrSubPos(const StaticStr* src, const StaticStr* str, int pos){
    int i = pos - 1;
    int j = 0;
    int next[MAXSIZE];
    StaticStrGetNext(str, next);
    while(i < src->length && j < str->length){
        if(j == -1 || src->ch[i] == str->ch[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    return j == str->length ? i + 1 - str->length : 0;
}
//辅助kmp算法的方法
void StaticStrGetNext(StaticStr* str, int next[]){
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
Status StaticStrReplace(StaticStr* src, const StaticStr* str1, const StaticStr* str2){
    if(!src || !str1 || !str2)
        return ERROR;
    int pos = 1;
    while((pos = StaticStrSubPos(src, str1, pos)) != 0){
        if(StaticStrDelete(src, pos, str1->length) == ERROR)//先删除str1
            return ERROR;
        if(StaticStrInsert(src, str2, pos) == ERROR)//再插入str2
            return ERROR;
        pos += str2->length;
    }
    return OK;
}
//SubGList里用
//将非空串分为 ','前后两个部分hstr为 ','之前的部分
Status StaticStrSever(StaticStr* str, StaticStr* hstr){
    if(!str || !hstr)
        return ERROR;
    int n, k = 0, i = 0;
    StaticStr* ch = NULL, *ch1 = NULL, *ch2 = NULL, *ch3 = NULL;
    StaticStrInit(&ch);
    StaticStrInit(&ch1);
    StaticStrInit(&ch2);
    StaticStrInit(&ch3);
    StaticStrAssign(ch1, ",");
    StaticStrAssign(ch2, "(");
    StaticStrAssign(ch3, ")");
    n = StaticStrLength(str);
    do{
        i++;
        StaticStrSubStr(ch, str, i, 1);
        if(StaticStrCompare(ch, ch2) == 0)
            k++;
        else if(StaticStrCompare(ch, ch3) == 0)
            k--;
    }while(i < n && (k != 0 || StaticStrCompare(ch, ch1) != 0));

    if(i < n){//说明找到了','
        StaticStrSubStr(hstr, str, 1, i - 1);
        StaticStrSubStr(str, str, i + 1, n - i);
    }
    else{//没有找到','
        StaticStrCopy(hstr, str);
        StaticStrClear(str);
    }
    return OK;
}

//打印静态串
Status StaticStrPrint(const StaticStr* str){
    if(!str || str->length < 0)
        return ERROR;
    if(str->length == 0){
        printf("静态串为空！\n");
        return OK;
    }
    for(int i = 0; i < str->length; i++){
        printf("%c", str->ch[i]);
    }
    printf("\n");
    return OK;
}
//返回pos位置的char类型元素
Status StaticStrGetChar(const StaticStr* str, int pos, char* ch){
    if(StaticStrEmpty(str) != FALSE || pos > str->length || pos < 1)
        return ERROR;
    *ch = str->ch[pos - 1];
    return OK;
}
