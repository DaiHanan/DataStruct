#include "TLinkedBTree.h"

//初始化二叉树
Status TLinkedBTreeInit(TLinkedBTree* tree){
    if(!tree)
        return ERROR;
    TLinkedBTreeDestroy(*tree);//先释放空间
    *tree = NULL;
    return OK;
}
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status TLinkedBTreeCreateByNums(TLinkedBTree* tree, int nums[], int len){
    if(!tree || !nums || len < 1)
        return ERROR;
    return _TLinkedBTreeCreateByNums(tree, nums, len, 0);
}
//创建二叉树，采用（先序）数组创建是为了Demo方便   子函数
Status _TLinkedBTreeCreateByNums(TLinkedBTree* tree, int nums[], int len, int idx){
    if(idx >= len || nums[idx] <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (TLinkedBTreeNode*)malloc(sizeof(TLinkedBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = nums[idx];
    (*tree)->parent = NULL;
    if(_TLinkedBTreeCreateByNums(&((*tree)->left), nums, len, idx * 2 + 1) != OK)//递归左子树
        return OVERFLOW;
    if((*tree)->left)
        (*tree)->left->parent = *tree;
    if(_TLinkedBTreeCreateByNums(&((*tree)->right), nums, len, idx * 2 + 2) != OK)//递归右子树
        return OVERFLOW;
    if((*tree)->right)
        (*tree)->right->parent = *tree;
    return OK;
}
//创建二叉树，动态创建
Status TLinkedBTreeCreate(TLinkedBTree* tree){
    if(!tree)
        return ERROR;
    TLinkedBTreeInit(tree);//先释放原空间
    printf("根");
    return _TLinkedBTreeCreate(tree);
}
//创建二叉树，动态创建子函数
Status _TLinkedBTreeCreate(TLinkedBTree* tree){
    int data;
    printf("结点：");
    scanf("%d", &data);
    if(data <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (TLinkedBTreeNode*)malloc(sizeof(TLinkedBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = data;
    (*tree)->parent = NULL;
    printf("左");
    if(_TLinkedBTreeCreate(&((*tree)->left)) != OK)//创建左子树
        return OVERFLOW;
    if((*tree)->left)
        (*tree)->left->parent = *tree;
    printf("右");
    if(_TLinkedBTreeCreate(&((*tree)->right)) != OK)//创建右子树
        return OVERFLOW;
    if((*tree)->right)
        (*tree)->right->parent = *tree;
    return OK;
}
//销毁二叉树
Status TLinkedBTreeDestroy(TLinkedBTree tree){
    if(!tree)
        return OK;
    TLinkedBTreeDestroy(tree->left);//销毁左子树
    TLinkedBTreeDestroy(tree->right);//销毁右子树
    free(tree);
    return OK;
}
//先序遍历二叉树
Status TLinkedBTreePreTraverse(TLinkedBTree tree, Status (*visit)(int*)){
    if(!tree)
        return OK;
    visit(&tree->data);
    if(TLinkedBTreePreTraverse(tree->left, visit) != OK)
        return ERROR;
    if(TLinkedBTreePreTraverse(tree->right, visit) != OK)
        return ERROR;
    return OK;
}
//中序遍历二叉树
Status TLinkedBTreeInTraverse(TLinkedBTree tree, Status (*visit)(int*)){
    if(!tree)
        return OK;
    if(TLinkedBTreeInTraverse(tree->left, visit) != OK)
        return ERROR;
    visit(&tree->data);
    if(TLinkedBTreeInTraverse(tree->right, visit) != OK)
        return ERROR;
    return OK;
}
//后序遍历二叉树
Status TLinkedBTreePostTraverse(TLinkedBTree tree, Status (*visit)(int*)){
    if(!tree)
        return OK;
    if(TLinkedBTreePostTraverse(tree->left, visit) != OK)
        return ERROR;
    if(TLinkedBTreePostTraverse(tree->right, visit) != OK)
        return ERROR;
    visit(&tree->data);
    return OK;
}
//层次遍历二叉树
Status TLinkedBTreeLevelTraverse(TLinkedBTree tree, Status (*visit)(int*)){
    if(!tree || !visit)
        return ERROR;
    //使用简易队列
    int front = 0, tail = 0;
    TLinkedBTreeNode** queue = (TLinkedBTreeNode**)
    malloc(sizeof(TLinkedBTreeNode*) * TLinkedBTreeLength(tree));//队列长度为tree长度
    if(!queue)
        return OVERFLOW;
    queue[tail++] = tree;
    TLinkedBTreeNode* p;
    while(tail != front){
        p = queue[front++];
        visit(&p->data);
        if(p->left)
            queue[tail++] = p->left;//左子树入队
        if(p->right)
            queue[tail++] = p->right;//右子树入队
    }
    free(queue);
    return OK;
}
//返回二叉树长度（元素个数）
int TLinkedBTreeLength(const TLinkedBTree tree){
    if(!tree)
        return 0;
    int len = 0;
    len += TLinkedBTreeLength(tree->left);
    len += TLinkedBTreeLength(tree->right);
    return len + 1;
}
//返回二叉树深度
int TLinkedBTreeDepth(const TLinkedBTree tree){
    if(!tree)
        return 0;
    int dep = 0;
    int left = TLinkedBTreeDepth(tree->left);
    int right = TLinkedBTreeDepth(tree->right);
    dep = left > right ? left : right;
    return dep + 1;
}
//返回二叉树带权路径长度 （WPL = weighted path length）
int TLinkedBTreeWPL(const TLinkedBTree tree){
    return _TLinkedBTreeWPL(tree, 1);
}
//返回二叉树带权路径长度子函数
int _TLinkedBTreeWPL(const TLinkedBTree tree, int dep){
    static int wpl = 0;//不会因为递归而刷新
    if(!tree)
        return wpl;
    if(!tree->left && !tree->right)//叶子结点
        wpl += tree->data * dep;
    _TLinkedBTreeWPL(tree->left, dep + 1);
    _TLinkedBTreeWPL(tree->right, dep + 1);
    return wpl;
}
//打印根到某个节点的路径
Status TLinkedBTreePath(const TLinkedBTree tree, int num){
    TLinkedBTreeNode* p = NULL;
    if(!tree || TLinkedBTreeContain(tree, num, &p) == FALSE)//查找该结点
        return ERROR;
    printf("（结点）");
    while(p && p->parent){
        printf("%d <- ", p->data);
        p = p->parent;
    }
    if(p)
        printf("（根）%d", p->data);
    return OK;
}
//验证元素num是否在该树里，并返回该结点
Status TLinkedBTreeContain(const TLinkedBTree tree, int num, TLinkedBTree* node){
    if(!tree)
        return FALSE;
    if(tree->data == num){
        *node = tree;
        return TRUE;
    }
    if(TLinkedBTreeContain(tree->left, num, node) == TRUE ||
       TLinkedBTreeContain(tree->right, num, node) == TRUE)
        return TRUE;
    return FALSE;
}
//简单打印函数
Status TLinkedBTreeVisit(int* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
