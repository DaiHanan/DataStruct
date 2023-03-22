#include "ThreadBTree.h"

//初始化二叉树
Status ThreadBTreeInit(ThreadBTree* tree){
    if(!tree)
        return ERROR;
    ThreadBTreeDestroy(*tree);//先释放空间
    *tree = NULL;
    return OK;
}
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status ThreadBTreeCreateByNums(ThreadBTree* tree, int nums[], int len){
    if(!tree || !nums || len < 1)
        return ERROR;
    return _ThreadBTreeCreateByNums(tree, nums, len, 0);
}
//创建二叉树，采用（先序）数组创建是为了Demo方便   子函数
Status _ThreadBTreeCreateByNums(ThreadBTree* tree, int nums[], int len, int idx){
    if(idx >= len || nums[idx] <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (ThreadBTreeNode*)malloc(sizeof(ThreadBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = nums[idx];
    (*tree)->lTag = Link;
    (*tree)->rTag = Link;
    if(_ThreadBTreeCreateByNums(&((*tree)->left), nums, len, idx * 2 + 1) != OK)//递归左子树
        return OVERFLOW;
    if(_ThreadBTreeCreateByNums(&((*tree)->right), nums, len, idx * 2 + 2) != OK)//递归右子树
        return OVERFLOW;
    return OK;
}
//创建二叉树，动态创建
Status ThreadBTreeCreate(ThreadBTree* tree){
    if(!tree)
        return ERROR;
    ThreadBTreeInit(tree);//先释放原空间
    printf("根");
    return _ThreadBTreeCreate(tree);
}
//创建二叉树，动态创建子函数
Status _ThreadBTreeCreate(ThreadBTree* tree){
    int data;
    printf("结点：");
    scanf("%d", &data);
    if(data <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (ThreadBTreeNode*)malloc(sizeof(ThreadBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = data;
    (*tree)->lTag = Link;
    (*tree)->rTag = Link;
    printf("左");
    if(_ThreadBTreeCreate(&((*tree)->left)) != OK)//创建左子树
        return OVERFLOW;
    printf("右");
    if(_ThreadBTreeCreate(&((*tree)->right)) != OK)//创建右子树
        return OVERFLOW;
    return OK;
}
//销毁二叉树
Status ThreadBTreeDestroy(ThreadBTree tree){
    if(!tree)
        return OK;
    ThreadBTreeDestroy(tree->left);//销毁左子树
    ThreadBTreeDestroy(tree->right);//销毁右子树
    free(tree);
    return OK;
}
//线索化二叉树（中序）
Status ThreadBTreeInThreading(ThreadBTree* head, ThreadBTree tree){
    if(!head)
        return ERROR;
    *head = (ThreadBTreeNode*)malloc(sizeof(ThreadBTreeNode));
    if(!*head)
        return OVERFLOW;
    if(!tree)//空树
        (*head)->left = *head;
    else{
        ThreadBTreeNode* pre = *head;
        (*head)->left = tree;
        _ThreadBTreeInThreading(tree, &pre);
        //此时pre指向最后一个结点
        pre->rTag = Thread;
        pre->right = *head;
        (*head)->right = pre;
    }
    return OK;
}
//线索化二叉树（中序）子函数， pre存当前结点的前一个结点
Status _ThreadBTreeInThreading(ThreadBTree tree, ThreadBTree* pre){
    if(tree){
        _ThreadBTreeInThreading(tree->left, pre);
        //线索化
        if(!tree->left){
            tree->lTag = Thread;
            tree->left = *pre;
        }
        if(!(*pre)->right){
            (*pre)->rTag = Thread;
            (*pre)->right = tree;
        }
        *pre = tree;//更新pre
        _ThreadBTreeInThreading(tree->right, pre);
    }
    return OK;
}
//遍历二叉树（中序）
Status ThreadBTreeInTraverse(ThreadBTree head, Status (*visit)(int*)){
    if(!head)
        return ERROR;
    ThreadBTreeNode* p = head->left;//第一个结点
    while(p != head){
        while(p->lTag == Link)
            p = p->left;
        visit(&p->data);
        while(p->rTag == Thread && p->right != head){
            p = p->right;
            visit(&p->data);
        }
        p = p->right;
    }
    return OK;
}
//简单打印函数
Status ThreadBTreeVisit(int* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
