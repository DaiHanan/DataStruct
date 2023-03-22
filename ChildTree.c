#include "ChildTree.h"

//创建树
Status ChildTreeCreate(CTree** tree){
    if(!tree)
        return ERROR;
    //利用createByNums函数创建
    int nums[MAXSIZE][2];

    printf("请输入结点个数：");
    int n;//临时存储结点个数
    scanf("%d", &n);
    while(getchar() != '\n');//清空输入流
    printf("请输入结点数据和其双亲下标：（空格隔开）\n");
    for(int i = 0; i < n; i++){//赋值结点信息
        scanf("%d %d", &nums[i][0], &nums[i][1]);
        while(getchar() != '\n');//清空输入流
    }
    return ChildTreeCreateByNums(tree, nums, n);
}
//通过数组创建树，方便测试
Status ChildTreeCreateByNums(CTree** tree, int nums[][2], int size){
    if(!tree || !nums || size < 1 || size > MAXSIZE)
        return ERROR;
    ChildTreeDestroy(*tree);//先释放原先内存
    *tree = (CTree*)malloc(sizeof(CTree));
    if(!*tree)
        return OVERFLOW;//申请内存失败
    (*tree)->n = size;
    for(int i = 0; i < size; i++){
        (*tree)->nodes[i].data = nums[i][0];//初始化数据
        (*tree)->nodes[i].first = NULL;//初始化指针
    }
    for(int i = 0; i <size; i++){//初始化子节点
        if(nums[i][1] == -1){//根节点
            (*tree)->r = i;
            continue;
        }
        //该结点（i）的双亲结点的第一个孩子链表结点，有点绕
        CNode* p = (*tree)->nodes[nums[i][1]].first;
        //接着找到该链表的尾结点
        while(p && p->next)
            p = p->next;
        //创建新的孩子链表结点
        CNode* newNode = (CNode*)malloc(sizeof(CNode));
        if(!newNode)
            return OVERFLOW;//申请内存失败
        newNode->child = i;//配置孩子下标
        //交换结点指针，尾插法，为了保持树的顺序
        if(!p){//first指针为NULL
            newNode->next = p;
            (*tree)->nodes[nums[i][1]].first = newNode;
        }else{
            p->next = newNode;
            newNode->next = NULL;
        }
    }
    return OK;
}
//销毁树
Status ChildTreeDestroy(CTree* tree){
    if(!tree)
        return ERROR;
    for(int i = 0; i < tree->n; i++){
        CNode* p = tree->nodes[i].first, *q;
        while(p){
            q = p->next;
            free(p);
            p = q;
        }
    }
    free(tree);
    return OK;
}
//获得结点的深度，未找到返回0
int ChildTreeNodeDepth(const CTree* tree, ElemType num){
    if(!tree || tree->n < 1)
        return ERROR;
    int dep = 1, i = 0;
    for(; i < tree->n; i++){//循环找到该结点的下标
        if(tree->nodes[i].data == num)
            break;
    }
    if(i == tree->n)//未找到
        return 0;
    while(i != tree->r){
        int flag = 0;
        for(int j = 0; j < tree->n; j++){//for循环找到下标为i的结点的双亲结点
            CNode* p = tree->nodes[j].first;
            while(p){
                if(p->child == i){//找到
                    i = j;
                    dep++;
                    flag = 1;
                    break;
                }
                p = p->next;
            }
            if(flag == 1)
                break;
        }
    }
    return dep;
}
//求树的高度
int ChildTreeDepth(const CTree* tree){
    if(!tree || tree->n < 0)
        return ERROR;
    if(tree->n == 0)//树长度为零
        return 0;
    int max = 1;//最大结点深度，即树的深度
    for(int i = 0; i < tree->n; i++){
        int dep = ChildTreeNodeDepth(tree, tree->nodes[i].data);
        max = max > dep ? max : dep;
    }
    return max;
}
//先根序遍历
Status ChildTreePreTraverse(const CTree* tree, Status (*visit)(ElemType*)){
    if(!tree || tree->n < 0 || !visit)
        return ERROR;
    if(tree->n == 0){
        printf("该树为空！\n");
        return OK;
    }
    return _ChildTreePreTraverse(tree, 0, visit);
}
//先根序遍历子函数，index当前结点下标
Status _ChildTreePreTraverse(const CTree* tree, int index, Status (*visit)(ElemType*)){
    if(visit(&tree->nodes[index].data) != OK)//先操作
        return ERROR;
    //后递归
    CNode* p = tree->nodes[index].first;
    while(p){
        _ChildTreePreTraverse(tree, p->child, visit);
        p = p->next;
    }
    return OK;
}
//后根序遍历
Status ChildTreePostTraverse(const CTree* tree, Status (*visit)(ElemType*)){
    if(!tree || tree->n < 0 || !visit)
        return ERROR;
    if(tree->n == 0){
        printf("该树为空！\n");
        return OK;
    }
    return _ChildTreePostTraverse(tree, 0, visit);
}
//后根序遍历子函数，index当前结点下标
Status _ChildTreePostTraverse(const CTree* tree, int index, Status (*visit)(ElemType*)){
    //先递归
    CNode* p = tree->nodes[index].first;
    while(p){
        _ChildTreePostTraverse(tree, p->child, visit);
        p = p->next;
    }
    if(visit(&tree->nodes[index].data) != OK)//后操作
        return ERROR;
    return OK;
}
//层次遍历
Status ChildTreeLevelTraverse(const CTree* tree, Status (*visit)(ElemType*)){
    if(!tree || tree->n < 0 || !visit)
        return ERROR;
    if(tree->n == 0){
        printf("该树为空！\n");
        return OK;
    }
    //创建临时队列，装各结点下标
    int* queue = (int*)malloc(sizeof(int) * tree->n);
    int h = 0, t = 0;
    //先把根节点装入队尾
    queue[t++] = tree->r;
    while(h != t){
        int index = queue[h++];//获得队首下标
        //while把该结点所有子节点放入队列
        CNode* p = tree->nodes[index].first;
        while(p){
            queue[t++] = p->child;
            p = p->next;
        }
        if(visit(&tree->nodes[index].data) != OK)//操作该结点
            return ERROR;
    }
    free(queue);
    return OK;
}
//根到节点的路径
Status ChildTreePath(const CTree* tree, ElemType num){
    if(!tree || tree->n <= 0)
        return ERROR;
    int i = 0;
    for(; i < tree->n; i++){//循环找到该结点下标
        if(tree->nodes[i].data == num)
            break;
    }
    if(i == tree->n)//未找到
        return 0;
    printf("（结点）");
    while(i != tree->r){
        printf("%d <- ", tree->nodes[i].data);
        int flag = 0;
        for(int j = 0; j < tree->n; j++){//for循环找到下标为i的结点的双亲结点
            CNode* p = tree->nodes[j].first;
            while(p){
                if(p->child == i){//找到
                    i = j;
                    flag = 1;
                    break;
                }
                p = p->next;
            }
            if(flag == 1)
                break;
        }
    }
    printf("（根）%d", tree->nodes[i].data);
}
//简单打印函数
Status ChildTreeVisit(ElemType* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
