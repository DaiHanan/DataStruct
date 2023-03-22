#include "CSTree.h"

//创建树
Status CSTreeCreate(CSTree* tree){
    if(!tree)
        return ERROR;
    CSTreeDestroy(*tree);//先释放原空间
    printf("根");
    return _CSTreeCreate(tree);
}
//创建树子函数
Status _CSTreeCreate(CSTree* tree){
    int data;
    printf("结点：");
    scanf("%d", &data);
    if(data <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (CSNode*)malloc(sizeof(CSNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = data;
    printf("孩子");
    if(_CSTreeCreate(&((*tree)->firstchild)) != OK)//创建孩子树
        return OVERFLOW;
    printf("兄弟");
    if(_CSTreeCreate(&((*tree)->nextsibling)) != OK)//创建兄弟树
        return OVERFLOW;
    return OK;
}
//通过（完全二叉树）数组创建树，方便测试
Status CSTreeCreateByNums(CSTree* tree, int nums[], int size){
    if(!tree || !nums || size < 1)
        return ERROR;
    return _CSTreeCreateByNums(tree, nums, size, 0);
}
//通过（完全二叉树）数组创建树，方便测试 子函数
Status _CSTreeCreateByNums(CSTree* tree, int nums[], int size, int idx){
    if(idx >= size || nums[idx] <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (CSNode*)malloc(sizeof(CSNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = nums[idx];
    if(_CSTreeCreateByNums(&((*tree)->firstchild), nums, size, idx * 2 + 1) != OK)//递归孩子树
        return OVERFLOW;
    if(_CSTreeCreateByNums(&((*tree)->nextsibling), nums, size, idx * 2 + 2) != OK)//递归兄弟树
        return OVERFLOW;
    return OK;
}
//销毁树
Status CSTreeDestroy(CSTree tree){
    if(!tree)
        return OK;
    CSTreeDestroy(tree->firstchild);//销毁左子树
    CSTreeDestroy(tree->nextsibling);//销毁右子树
    free(tree);
    return OK;
}
//求树的高度
int CSTreeDepth(const CSTree tree){
    if(!tree)//不存在时长度为0
        return 0;
    if(!tree->firstchild)//孩子不存在长度为1
        return 1;
    int max = 0, dep;
    CSNode* p = tree->firstchild;//指向第一个孩子
    while(p){
        dep = CSTreeDepth(p);//递归求深度
        max = max > dep ? max : dep;
        p = p->nextsibling;
    }
    return max + 1;
}
//求树的长度
int CSTreeLength(const CSTree tree){
    if(!tree)
        return 0;
    int len = 0;
    len += CSTreeLength(tree->firstchild);
    len += CSTreeLength(tree->nextsibling);
    return len + 1;
}
//先根序遍历
Status CSTreePreTraverse(const CSTree tree, Status (*visit)(ElemType*)){
    /*  本人发现先根遍历和二叉树的先序遍历规律相同
    （可能因为测试数据少造成，所以学习并采用了原本的先根遍历）
    if(!tree)
        return OK;
    if(visit(&tree->data) != OK)
        return ERROR;
    if(CSTreePreTraverse(tree->firstchild, visit) != OK)
        return ERROR;
    if(CSTreePreTraverse(tree->nextsibling, visit) != OK)
        return ERROR;
    return OK;
    */
    if(!tree)
        return OK;
    if(visit(&tree->data) != OK)//先操作
        return ERROR;
    CSNode* p = tree->firstchild;
    //后递归
    while(p){
        if(CSTreePreTraverse(p, visit) != OK)
            return ERROR;
        p = p->nextsibling;
    }
    return OK;
}
//后根序遍历
Status CSTreePostTraverse(const CSTree tree, Status (*visit)(ElemType*)){
    /*用少量的数据发现后根遍历和二叉树的中序遍历相同，但为了保险暂时没有采用
    if(!tree)
        return OK;
    if(CSTreePostTraverse(tree->firstchild, visit) != OK)
        return ERROR;
    visit(&tree->data);
    if(CSTreePostTraverse(tree->nextsibling, visit) != OK)
        return ERROR;
    return OK;
    */
    if(!tree)
        return OK;
    CSNode* p = tree->firstchild;
    //先递归
    while(p){
        if(CSTreePostTraverse(p, visit) != OK)
            return ERROR;
        p = p->nextsibling;
    }
    if(visit(&tree->data) != OK)//后操作
        return ERROR;
    return OK;
}
//层次遍历
Status CSTreeLevelTraverse(const CSTree tree, Status (*visit)(ElemType*)){
    if(!tree || !visit)
        return ERROR;
    int len = CSTreeLength(tree);
    if(len == 0)
        return OK;
    //创建临时队列，装各结点下标
    CSTree* queue = (CSTree*)malloc(sizeof(CSTree) * len);
    int h = 0, t = 0;
    //先操作根结点
    if(visit(&tree->data) != OK){
        free(queue);
        return ERROR;
    }
    //把根节点装入队尾
    queue[t++] = tree;
    while(h != t){
        CSNode* p = queue[h++]->firstchild;//获取队首结点的孩子结点
        while(p){//操作并入队所有孩子结点
            if(visit(&p->data) != OK){
                free(queue);
                return ERROR;
            }
            queue[t++] = p;
            p = p->nextsibling;
        }
    }
    free(queue);//释放临时数组空间
    return OK;
}
//验证元素num是否在该树里
Status CSTreeContain(const CSTree tree, ElemType num){
    if(!tree)
        return FALSE;
    if(tree->data == num ||
       CSTreeContain(tree->firstchild, num) == TRUE ||
       CSTreeContain(tree->nextsibling, num) == TRUE)
        return TRUE;
    return FALSE;
}
//根到节点的路径
Status CSTreePath(const CSTree tree, ElemType num){
    if(!tree || CSTreeContain(tree, num) == FALSE)
        return ERROR;

    typedef struct{//临时结构体
        CSNode* node;//当前结点指针
        int parent;//存放双亲在队列中的位置
    }snode;

    //创建队列
    snode* Qu = (snode*)malloc(sizeof(snode) * CSTreeLength(tree));
    if(!Qu)
        return OVERFLOW;

    int front = -1, rear = 0, curr;
    Qu[rear].node = tree;//根节点进入队列
    Qu[rear].parent = -1;//根节点没有双亲
    CSNode* node = tree;
    while(front < rear){
        front++;
        node = Qu[front].node;//取队头
        if(node->data == num){
            printf("（结点）");
            curr = front;
            while(Qu[curr].parent != -1){
                printf("%d <- ", Qu[curr].node->data);
                curr = Qu[curr].parent;
            }
            printf("（根）%d", Qu[curr].node->data);
            break;
        }
        if(node->firstchild){//孩子树入队
            Qu[++rear].node = node->firstchild;
            Qu[rear].parent = front;//孩子结点的双亲为该结点
        }
        if(node->nextsibling){//兄弟树入队
            Qu[++rear].node = node->nextsibling;
            Qu[rear].parent = Qu[front].parent;//兄弟结点的双亲下标为该结点的双亲下标
        }
    }
    free(Qu);
    return OK;
}
//简单打印函数
Status CSTreeVisit(ElemType* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
