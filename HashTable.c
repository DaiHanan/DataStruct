#include "HashTable.h"

//初始化
Status HashTableInit(HashTable* h){
    if(!h)
        return ERROR;
    //设置元素
    for(int i = 0; i < HASHSIZE; i++)
        h->data[i] = NULLKEY;
    //设置个数
    h->count = 0;
    return OK;
}
//插入
Status HashTableInsert(HashTable* h, ElemType key){
    if(!h)
        return ERROR;
    int addr = Hash(key);
    //最多查找100次，防止死循环
    int time = 0;
    //二次探测用
    int temp = addr, count = 1, flag = -1;

    while((addr < 0 || addr >= HASHSIZE || h->data[addr] != NULLKEY) && ++time <= 100){
        /**开放定址法*/
        //线性探测再散列
        addr = (addr + 1) % HASHSIZE;
        //二次探测再散列 +1，-1，+2，-2
        //if(flag > 0)
        //    flag = -flag;
        //else{
        //    flag = count;
        //    count *= 2;
        //}
        //addr = (temp + flag) % HASHSIZE;
        //伪随机探测再散列
        //if(flag > 0)
        //    flag = -flag;
        //else
        //    flag = rand() % HASHSIZE;
        //addr = (temp + flag) % HASHSIZE;
        /**再哈希法*/
        //addr = Hash1(key);
        /**链地址法 —— 需要重设HashTable结构*/
        //设哈希表里元素数组为结点形式node，node里有元素elem和next指针
        //node* newNode = (node*)malloc(sizeof(node));
        //newNode->elem = key;
        //头插法
        //newNode->next = h->data[addr];
        //h->data[addr] = newNode;
        //return OK;
        /**建立一个公共溢出区 —— 需要重设HashTable结构*/
        //设哈希表里有溢出区extra和当前元素extraCount和溢出区大小extraSize
        //if(h->extraCount < extraSize){
        //    h->extra[extraCount++] = key;
        //    return OK;
        //}
        //else
        //    return ERROR;
    }
    if(time > 100)//找位失败
        return ERROR;
    //找位成功
    //printf("%d\n", addr);//打印插入下标
    h->data[addr] = key;
    return OK;
}

//查找(地址)
Status HashTableFind(HashTable h, ElemType key, int* addr){
    *addr = Hash(key);
    int time = 0;
    //二次探测用
    int temp = *addr, count = 1, flag = -1;
    //搜索100次
    while((*addr < 0 || *addr >= HASHSIZE || h.data[*addr] != key) && ++time <= 100){
        /**开放定址法*/
        //线性探测再散列
        *addr = (*addr + 1) % HASHSIZE;
        //二次探测再散列 +1，-1，+2，-2
        //if(flag > 0)
        //    flag = -flag;
        //else{
        //    flag = count;
        //    count *= 2;
        //}
        //*addr = (temp + flag) % HASHSIZE;
        //伪随机探测再散列
        //if(flag > 0)
        //    flag = -flag;
        //else
        //    flag = rand() % HASHSIZE;
        //*addr = (temp + flag) % HASHSIZE;
        /**再哈希法*/
        //*addr = Hash1(key);
        /**链地址法 —— 需要重设HashTable结构*/
        //设哈希表里元素数组为结点形式node，node里有元素elem和next指针
        //地址还需要返回对应的深度，直接return深度
        //int dep = 1;
        //node* p = h.data[*addr];
        //while(p){
        //    if(p->elem == key)
        //        return dep;
        //    p = p->next;
        //    dep++;
        //}
        //return -1;
        /**建立一个公共溢出区 —— 需要重设HashTable结构*/
        //设哈希表里有溢出区extra和当前元素extraCount和溢出区大小extraSize
        //for(int i = 0; i < h.extraCount; i++)
        //    if(h.extra[i] == key){
        //        *addr = i;
        //        return -2;//表示元素在溢出区
        //    }
        //return ERROR;
    }
    if(time > 100)
        return ERROR;
    return OK;
}
//Hash函数
int Hash(ElemType key){
    //直接定址法
    return key * 2 + 3;
    //数字分析法 设个位数不同，取个位为基准
    //return key % 10;
    //平方取中法 设取十位上的数
    //return key * key / 10 % 10;
    //折叠法 取二进制后四位累加
    //int res = 0;
    //for(int i = 0; i < 4; i++){
    //    res += key & 1;
    //    key >> 1;
    //}
    //return res;
    //除留余数法
    //return key % HASHSIZE;
    //随机数法
    //srand((int)time(NULL));
    //return rand() % key;
}
//Hash函数备用
int Hash1(ElemType key){
    //平方取中法 设取十位上的数
    return key * key / 10 % 10;
}
