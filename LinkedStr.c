#include "LinkedStr.h"

//初始化传入的块链串（创建空串）
Status LinkedStrInit(LinkedStr** str){
    if(!str)
        return ERROR;
    LinkedStrDestroy(*str);//先释放*str所有空间
    *str = (LinkedStr*)malloc(sizeof(LinkedStr));
    if(!*str)
        return OVERFLOW;
    (*str)->head = NULL;
    (*str)->tail = NULL;
    (*str)->length = 0;
    return OK;
}
//判断传入的块链串是否为空串
Status LinkedStrEmpty(const LinkedStr* str){
    if(!str)
        return ERROR;
    //必须同时满足三个条件
    if(!str->head && !str->tail && str->length == 0)
        return TRUE;
    return FALSE;
}
//生成一个值为字符串chs的块链串
Status LinkedStrAssign(LinkedStr* str, char chs[]){
    /*
        因为调用init函数需要二级指针，所以这里拐了几个弯
        不清楚为什么不能直接传str，但是这样也不会泄露空间
    */
    LinkedStr s = *str;
    LinkedStr* ps = &s;
    if(LinkedStrInit(&ps) != OK)//初始化
        return OVERFLOW;
    *str = *ps;
    ////////////////////////////////////////////////////
    int len = 0;
    while(chs[len++] != '\0');
    len--;//while多加了一次
    if(!len)
        return OK;//字符串为空直接返回
    int i = len / BLOCK_SIZE;//整块链数
    int j = len % BLOCK_SIZE;//剩余字符
    if(j > 0)
        i++;//i为块链数
    int count = 0;
    for(int k = 1; k <= i; k++){
        //创建Block
        Block* block = (Block*)malloc(sizeof(Block));
        if(!block)
            return OVERFLOW;
        block->next = NULL;
        if(k == 1)//第一次需要关联head指针
            str->head = str->tail = block;
        else{
            str->tail->next = block;
            str->tail = block;
        }
        //复制元素
        for(count = 0; count < BLOCK_SIZE && (count + (k - 1) * BLOCK_SIZE) < len; count++){
            block->ch[count] = chs[count + (k - 1) * BLOCK_SIZE];
        }
    }
    //最后一个块链没满时填充\0
    while(count < BLOCK_SIZE){
        str->tail->ch[count++] = '\0';
    }
    str->length = len;//记录长度
    return OK;
}
//拷贝块链串
Status LinkedStrCopy(LinkedStr* str, const LinkedStr* src){
    if(!str || !src)
        return ERROR;
    //可以判断两个串的长度来获取/释放空间，这里用的暴力初始化
    LinkedStr s = *str;
    LinkedStr* ps = &s;
    if(LinkedStrInit(&ps) != OK)//初始化
        return OVERFLOW;
    *str = s;
    Block* p = src->head;
    while(p){
        //创建Block
        Block* block = (Block*)malloc(sizeof(Block));
        if(!block)
            return OVERFLOW;
        block->next = NULL;
        if(p == src->head)//第一次需要关联head指针
            str->head = str->tail = block;
        else{
            str->tail->next = block;
            str->tail = block;
        }
        //现在新加的block在str的tail指针上
        for(int i = 0; i < BLOCK_SIZE; i++)
            block->ch[i] = p->ch[i];
        p = p->next;
    }
    //记录长度
    str->length = src->length;
}
//将块链串清空
Status LinkedStrClear(LinkedStr* str){
    if(!str)
        return ERROR;
    Block* p = str->head;
    while(p){
        Block* q = p->next;
        free(p);
        p = q;
    }
    str->head = str->tail = NULL;
    str->length = 0;
    return OK;
}
//删除传入的块链串
Status LinkedStrDestroy(LinkedStr* str){
    if(LinkedStrClear(str) == ERROR)
        return ERROR;
    free(str);
    return OK;
}
//连接块链串str1和str2，用res返回
Status LinkedStrConcat(LinkedStr* res, const LinkedStr* str1, const LinkedStr* str2){
    if(!res || !str1 || !str2)
        return ERROR;
    LinkedStr s = *res;
    LinkedStr* ps = &s;
    if(LinkedStrInit(&ps) != OK)//初始化
        return OVERFLOW;
    *res = s;
    Block* p = str1->head;
    Block* q = str2->head;
    Block* r = res->head;
    int i = 0, j = 0, k = 0;//对应res, str1, str2当前的下标
    while(p || q){
        if(!r){
            //为res创建新的空间
            r = (Block*)malloc(sizeof(Block));
            if(!r)
                return OVERFLOW;
            r->next = NULL;
            if(res->head == NULL)//第一次需要关联head指针
                res->head = res->tail = r;
            else{
                res->tail->next = r;
                res->tail = r;
            }
        }
        if(p){//先复制str1中元素
            while(p && p->ch[j] != '\0'){
                r->ch[i] = p->ch[j];
                i = (i + 1) % BLOCK_SIZE;
                j = (j + 1) % BLOCK_SIZE;
                //str1当前块结束
                if(!j || !p->ch[j])
                    p = p->next;
                //res当前块结束
                if(!i){
                    r = r->next;
                    break;
                }
            }
        }
        else{//再复制str2中元素
            while(q && q->ch[k]){
                r->ch[i] = q->ch[k];
                i = (i + 1) % BLOCK_SIZE;
                k = (k + 1) % BLOCK_SIZE;
                //str2当前块结束
                if(!k || !q->ch[k])
                    q = q->next;
                //res当前块结束
                if(!i){
                    r = r->next;
                    break;
                }
            }
        }
    }
    while(r && i < BLOCK_SIZE)
        r->ch[i++] = '\0';
    res->length = str1->length + str2->length;
    return OK;
}
//获得块链串长度
int LinkedStrLength(const LinkedStr* str){
    if(!str || str->length < 0)
        return ERROR;
    return str->length;
}
//比较传入的两个块链串大小，str1 > str2 返回正数，....， 相等返回0
//注：不再检查ERROR
int LinkedStrCompare(const LinkedStr* str1, const LinkedStr* str2){
    Block* p = str1->head;
    Block* q = str2->head;
    int i = 0;//当前下标
    while(p && q){
        if(p->ch[i] != q->ch[i])
            return p->ch[i] - q->ch[i];
        i = (i + 1) % BLOCK_SIZE;
        if(!i){
            p = p->next;
            q = q->next;
        }
    }
    if(!p && !q){
        return 0;
    }
    return str1->length - str2->length;
}
//返回块链串中pos位置开始长为len的子串
Status LinkedStrSubStr(LinkedStr* sub, const LinkedStr* src, int pos, int len){
    if(!src || len < 0 || pos < 1 || pos + len - 1 > src->length)
        return ERROR;
    LinkedStr s = *sub;
    LinkedStr* ps = &s;
    if(LinkedStrInit(&ps) != OK)//初始化
        return OVERFLOW;
    *sub = s;
    if(len == 0)//长度为0不需要继续
        return OK;
    int i = (pos - 1) / BLOCK_SIZE;//pos位置前的块链数
    int j = (pos - 1) % BLOCK_SIZE;//pos位置在块链的下标
    Block* p = src->head;
    for(int m = 0; m < i; m++){
        p = p->next;//p最终指向pos位置所在块链
    }
    int k = 0;//sub当前下标
    Block* q = sub->head;//sub当前块链
    for(int m = 0; m < len; m++){
        if(!q){
            //为sub创建新的空间
            q = (Block*)malloc(sizeof(Block));
            if(!q)
                return OVERFLOW;
            q->next = NULL;
            if(sub->head == NULL)//第一次需要关联head指针
                sub->head = sub->tail = q;
            else{
                sub->tail->next = q;
                sub->tail = q;
            }
        }
        q->ch[k] = p->ch[j];
        k = (k + 1) % BLOCK_SIZE;
        j = (j + 1) % BLOCK_SIZE;
        if(!j)
            p = p->next;
        if(!k)
            q = q->next;
    }
    while(q && k < BLOCK_SIZE)
        q->ch[k++] = '\0';
    sub->length = len;
    return OK;
}
//在块链串str1中pos位置插入另一块链str2
Status LinkedStrInsert(LinkedStr* str1, const LinkedStr* str2, int pos){
    if(!str1 || !str2 || pos < 1 || pos > str1->length + 1)
        return ERROR;
    //思路：把str1、str2中字符都提取出来，再用之前的assign函数赋值
    char* chs = (char*)malloc(sizeof(char) * (str1->length + str2->length + 1));//加一为了存'\0'
    if(!chs)
        return OVERFLOW;
    Block* p = str1->head;//str1当前块链
    int i = 0;//str1当前下标
    int k = 0;//chs当前下标
    //复制str1中pos位置前的字符
    for(; k < pos - 1; k++){
        chs[k] = p->ch[i];
        i = (i + 1) % BLOCK_SIZE;
        if(!i)
            p = p->next;//指向下一个块链
    }
    Block* q = str2->head;//str2当前块链
    int j = 0;//str2当前下标
    //复制str2中的字符
    for(;k < pos + str2->length - 1; k++){
        chs[k] = q->ch[j];
        j = (j + 1) % BLOCK_SIZE;
        if(!j)
            q = q->next;//指向下一个块链
    }
    //复制str1中pos后的元素
    for(;k < str1->length + str2->length; k++){
        chs[k] = p->ch[i];
        i = (i + 1) % BLOCK_SIZE;
        if(!i)
            p = p->next;//指向下一个块链
    }
    chs[str1->length + str2->length] = '\0';
    int flag = LinkedStrAssign(str1, chs);
    free(chs);
    return flag == OVERFLOW ? OVERFLOW : OK;
}
//在块链串str中删除pos位置开始长len的子串
Status LinkedStrDelete(LinkedStr* str, int pos, int len){
    if(!str || pos < 1 || len < 0 || pos + len - 1 > str->length)
        return ERROR;
    //思路和insert函数相似
    char* chs = (char*)malloc(sizeof(char) * (str->length - len + 1));//加一为了存'\0'
    if(!chs)
        return OVERFLOW;
    Block* p = str->head;//str1当前块链
    int i = 0;//str1当前下标
    int k = 0;//chs当前下标
    //复制str1中pos位置前的字符
    for(; k < pos - 1; k++){
        chs[k] = p->ch[i];
        i = (i + 1) % BLOCK_SIZE;
        if(!i)
            p = p->next;//指向下一个块链
    }
    //根据len改变p和i
    i += len;
    for(int j = 0; j < i / BLOCK_SIZE; j++){
        p = p->next;
    }
    i = i % BLOCK_SIZE;

    //复制str1中pos + len后的元素
    for(;k < str->length - len; k++){
        chs[k] = p->ch[i];
        i = (i + 1) % BLOCK_SIZE;
        if(!i)
            p = p->next;//指向下一个块链
    }
    chs[str->length - len] = '\0';
    int flag = LinkedStrAssign(str, chs);
    free(chs);
    return flag == OVERFLOW ? OVERFLOW : OK;
}

//从pos位置开始找静态串src中子串str的位置未找到返回0（非kmp）
int LinkedStrSubPos(const LinkedStr* src, const LinkedStr* str, int pos){
    //暴风算法,速度慢
    if(LinkedStrEmpty(src) != FALSE ||
       LinkedStrEmpty(str) != FALSE ||
       pos < 1 || pos > src->length)
    return ERROR;
    int len1 = src->length;
    int len2 = str->length;
    LinkedStr* temp = NULL;
    LinkedStrInit(&temp);
    for(int i = pos; i <= len1 - len2 + 1; i++){
        if(LinkedStrSubStr(temp, src, i, len2) == ERROR){//取len2长度的子串
            LinkedStrDestroy(temp);//记得销毁temp空间
            return ERROR;
        }
        if(LinkedStrCompare(temp, str) == 0){//相等
            LinkedStrDestroy(temp);
            return i;
        }
    }
    LinkedStrDestroy(temp);
    return 0;
}

//用str2替换src中所有和str1相等的子串
Status LinkedStrReplace(LinkedStr* src, const LinkedStr* str1, const LinkedStr* str2){
    if(LinkedStrEmpty(src) != FALSE ||
       LinkedStrEmpty(str1) != FALSE ||
       LinkedStrEmpty(str2) != FALSE)
    return ERROR;
    int pos = 1;
    while((pos = LinkedStrSubPos(src, str1, pos)) != 0){
        if(LinkedStrDelete(src, pos, str1->length) == ERROR)//先删除str1
            return ERROR;
        if(LinkedStrInsert(src, str2, pos) == ERROR)//再插入str2
            return ERROR;
        pos += str2->length;
    }
    return OK;
}

//打印块链串
Status LinkedStrPrint(const LinkedStr* str){
    if(!str || str->length < 0)
        return ERROR;
    if(str->length == 0){
        printf("块链串为空！\n");
        return OK;
    }
    Block* p = str->head;
    for(int i = 0; i < str->length;){
        printf("%c", p->ch[i % BLOCK_SIZE]);
        if(++i % BLOCK_SIZE == 0)
            p = p->next;
    }
    printf("\n");
    return OK;
}
