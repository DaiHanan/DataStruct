#include "HuffManBTree.h"

//初始化待编码的字符
Status HTInitCode(HTCode hc[], int* n){
    if(!hc || !n)
        return ERROR;
    printf("请输入字符个数：");
    scanf("%d", &(*n));
    while(getchar() != '\n');
    printf("\n请输入全部字符（空格隔开）：\n");
    for(int i = 1; i <= *n; i++)
        scanf("%c", &hc[i].data);
    while(getchar() != '\n');
    printf("\n请输入字符对应的权重（空格隔开）：\n");
    for(int i = 1; i <= *n; i++)
        scanf("%d", &hc[i].weight);
    while(getchar() != '\n');
    return OK;
}
//用数组初始化待编码的字符
Status HTInitCodeByNums(HTCode hc[], char chars[], int weights[], int size){
    if(!hc || !chars || !weights || size < 1 || size > HTMAX)
        return ERROR;
    for(int i = 1; i <= size; i++)
        hc[i].data = chars[i - 1];
    for(int i = 1; i <= size; i++)
        hc[i].weight = weights[i - 1];
    return OK;
}
//获得[1,k]中parent == 0 且权重最小的两个结点，返回下标
Status HTSelect(HTNode hn[], int k, int* s1, int* s2){
    if(!hn || !s1 || !s2 || k < 1 || k > HTMAX * 2 - 1)
        return ERROR;
    for(int i = 1; i <= k; i++){
        if(hn[i].parent == 0){
                *s1 = i;
                break;
        }
    }
    for(int i = 1; i <= k; i++)
        if(hn[i].parent == 0 && hn[i].weight < hn[*s1].weight)
            *s1 = i;
    for(int i = 1; i <= k; i++){
        if(hn[i].parent == 0 && i != *s1){
                *s2 = i;
                break;
        }
    }
    for(int i = 1; i <= k; i++)
        if(i != *s1 && hn[i].parent == 0 && hn[i].weight < hn[*s2].weight)
            *s2 = i;
    return OK;
}
//构造哈夫曼树，并求出字符编码
Status HTCreate(HTNode hn[], HTCode hc[], int n){
    if(!hn || !hc || n < 1 || n > HTMAX)
        return ERROR;
    int m = 2 * n - 1;  //哈夫曼的结点个数
    for(int i = 1; i <= m; i++){
        if(i <= n)
            hn[i].weight = hc[i].weight;
        else
            hn[i].weight = 0;
        hn[i].left = hn[i].right = hn[i].parent = 0;
    }
    int s1, s2;
    for(int i = n + 1; i <= m; i++){
        HTSelect(hn, i - 1, &s1, &s2);
        hn[i].weight = hn[s1].weight + hn[s2].weight;
        hn[i].left = s1;
        hn[i].right = s2;
        hn[s1].parent = hn[s2].parent = i;
    }
    char cd[n];
    cd[n - 1] = '\0';
    int start;
    for(int i = 1; i <= n; i++){
        start = n - 1;
        for(int c = i, f = hn[c].parent; f; c = f, f = hn[f].parent){
            if(hn[f].left == c)//结点在左子树
                cd[--start] = '0';
            else//右子树
                cd[--start] = '1';
        }
        strcpy(hc[i].code, cd + start);
    }
    return OK;
}
