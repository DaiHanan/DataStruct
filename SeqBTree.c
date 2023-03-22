#include "SeqBTree.h"

//初始化二叉树
Status SeqBTreeInit(SeqBTree tree){
    if(!tree)
        return ERROR;
    for(int i = 0; i < MAXSIZE; i++)
        tree[i] = -1;
    return OK;
}
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status SeqBTreeCreateByNums(SeqBTree tree, int nums[], int len){
    if(!tree || !nums || len < 1)
        return ERROR;
    for(int i = 0; i < len; i++)
        tree[i] = nums[i];
    return OK;
}
//创建二叉树，动态创建
Status SeqBTreeCreate(SeqBTree tree){
    if(!tree)
        return ERROR;
    printf("根");
    return _SeqBTreeCreate(tree, 0);
}
//创建二叉树，动态创建子函数
Status _SeqBTreeCreate(SeqBTree tree, int idx){
    if(idx >= MAXSIZE || idx < 0)
        return OK;
    int num = -1;
    printf("结点：");
    scanf("%d", &num);
    tree[idx] = num;
    if(num <= 0)//不再创建
        return OK;
    printf("左");
    _SeqBTreeCreate(tree, 2 * idx + 1);//创建左子树
    printf("右");
    _SeqBTreeCreate(tree, 2 * idx + 2);//创建右子树
    return OK;
}
//先序遍历二叉树
Status SeqBTreePreTraverse(SeqBTree tree, Status (*visit)(int*)){
    if(!tree || !visit)
        return ERROR;
    return _SeqBTreePreTraverse(tree, visit, 0);
}
//先序遍历二叉树子函数
Status _SeqBTreePreTraverse(SeqBTree tree, Status (*visit)(int*), int idx){
    if(idx < 0 || idx >= MAXSIZE)
        return OK;
    if(tree[idx] > 0)
        visit(&tree[idx]);
    _SeqBTreePreTraverse(tree, visit, idx * 2 + 1);//左
    _SeqBTreePreTraverse(tree, visit, idx * 2 + 2);//右
    return OK;
}
//中序遍历二叉树
Status SeqBTreeInTraverse(SeqBTree tree, Status (*visit)(int*)){
    if(!tree || !visit)
        return ERROR;
    return _SeqBTreeInTraverse(tree, visit, 0);
}
//中序遍历二叉树子函数
Status _SeqBTreeInTraverse(SeqBTree tree, Status (*visit)(int*), int idx){
    if(idx < 0 || idx >= MAXSIZE)
        return OK;
    _SeqBTreeInTraverse(tree, visit, idx * 2 + 1);//左
    if(tree[idx] > 0)
        visit(&tree[idx]);
    _SeqBTreeInTraverse(tree, visit, idx * 2 + 2);//右
    return OK;
}
//后序遍历二叉树
Status SeqBTreePostTraverse(SeqBTree tree, Status (*visit)(int*)){
    if(!tree || !visit)
        return ERROR;
    return _SeqBTreePostTraverse(tree, visit, 0);
}
//后序遍历二叉树子函数
Status _SeqBTreePostTraverse(SeqBTree tree, Status (*visit)(int*), int idx){
    if(idx < 0 || idx >= MAXSIZE)
        return OK;
    _SeqBTreePostTraverse(tree, visit, idx * 2 + 1);//左
    _SeqBTreePostTraverse(tree, visit, idx * 2 + 2);//右
    if(tree[idx] > 0)
        visit(&tree[idx]);
    return OK;
}
//层次遍历二叉树
Status SeqBTreeLevelTraverse(SeqBTree tree, Status (*visit)(int*)){
    if(!tree || !visit)
        return ERROR;
    for(int i = 0; i < MAXSIZE; i++)
        if(tree[i] > 0)
            visit(&tree[i]);
    return OK;
}
//返回二叉树长度（元素个数）
int SeqBTreeLength(const SeqBTree tree){
    if(!tree)
        return ERROR;
    int len = 0;
    for(int i = 0; i < MAXSIZE; i++)
        if(tree[i] > 0)
            len++;
    return len;
}
//返回二叉树深度
int SeqBTreeDepth(const SeqBTree tree){
    if(!tree)
        return ERROR;
    return _SeqBTreeDepth(tree, 0);
}
//返回二叉树深度子函数
int _SeqBTreeDepth(const SeqBTree tree, int idx){
    if(idx < 0 || idx >= MAXSIZE || tree[idx] <= 0)
        return 0;
    int dep1, dep2;
    dep1 = _SeqBTreeDepth(tree, idx * 2 + 1);//左
    dep2 = _SeqBTreeDepth(tree, idx * 2 + 2);//右
    return dep1 > dep2 ? dep1 + 1 : dep2 + 1;
}
//返回二叉树带权路径长度 （WPL = weighted path length）
int SeqBTreeWPL(const SeqBTree tree){
    if(!tree)
        return ERROR;
    return _SeqBTreeWPL(tree, 0, 1);
}
//返回二叉树带权路径长度子函数
int _SeqBTreeWPL(const SeqBTree tree, int idx, int dep){
    static int wpl = 0;
    if(idx < 0 || idx >= MAXSIZE || tree[idx] <= 0)
        return wpl;
    int left = idx * 2 + 1;
    int right = left + 1;
    if(left >= 0 && left < MAXSIZE && tree[left] > 0)//递归左子树
        _SeqBTreeWPL(tree, left, dep + 1);
    if(right >= 0 && right < MAXSIZE && tree[right] > 0)//递归右子树
        _SeqBTreeWPL(tree, right, dep + 1);
    if(left >= 0 && left < MAXSIZE &&
       right >= 0 && right < MAXSIZE &&
       tree[left] <= 0 && tree[right] <= 0)//当前是叶子节点
       wpl += tree[idx] * dep;
    return wpl;
}
//打印根到某个节点的路径
Status SeqBTreePath(const SeqBTree tree, int num){
    if(!tree || num <= 0)
        return ERROR;
    int idx = 0;
    if(SeqBTreeContain(tree, num) == FALSE)
        return ERROR;
    for(;idx < MAXSIZE; idx++){
        if(tree[idx] == num)
            break;
    }
    int idxs[MAXSIZE], i = 0;//充当临时栈
    idxs[i++] = idx;
    while(idx != 0){
        if(idx % 2 == 1)//奇数，左子树
            idx = (idx - 1) / 2;
        else//偶数，右子树
            idx = (idx - 2) / 2;
        idxs[i++] = idx;
    }
    i--;
    printf("（根）");
    for(; i > 0;i--)
        printf("%d -> ", tree[idxs[i]]);
    printf("（节点）%d", tree[idxs[0]]);
    return OK;
}
//验证元素num是否在该树里
Status SeqBTreeContain(const SeqBTree tree, int num){
    for(int i = 0; i < MAXSIZE; i++)
        if(tree[i] == num)
            return TRUE;
    return FALSE;
}
//简单打印函数
Status SeqBTreeVisit(int* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
