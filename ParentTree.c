#include "ParentTree.h"

Status ParentTreeCreate(PTree** tree){
    if(!tree)
        return ERROR;
    ParentTreeDestroy(*tree);//释放原先内存
    *tree = (PTree*)malloc(sizeof(PTree));
    if(!*tree)
        return OVERFLOW;
    printf("请输入结点个数：");
    int n;//临时存储结点个数
    scanf("%d", &n);
    (*tree)->n = n;//更新结点个数
    while(getchar() != '\n');//清空输入流
    printf("请输入结点数据和其双亲下标：（空格隔开）\n");
    for(int i = 0; i < n; i++){//赋值结点信息
        scanf("%d %d", &(*tree)->nodes[i].data, &(*tree)->nodes[i].parent);
        while(getchar() != '\n');//清空输入流
    }
    for(int i = 0; i < n; i++){
        if((*tree)->nodes[i].parent == -1){//设置根结点
            (*tree)->r = i;
            break;
        }
    }
    return OK;
}
//通过数组创建树，方便测试
Status ParentTreeCreateByNums(PTree** tree, int nums[][2], int size){
    if(!tree || !nums || size < 1 || size > MAXSIZE)
        return ERROR;
    ParentTreeDestroy(*tree);
    *tree = (PTree*)malloc(sizeof(PTree));
    if(!*tree)
        return OVERFLOW;
    for(int i = 0; i < size; i++){
        (*tree)->nodes[i].data = nums[i][0];
        (*tree)->nodes[i].parent = nums[i][1];
    }
    for(int i = 0; i < size; i++)
        if((*tree)->nodes[i].parent == -1)//根结点
            (*tree)->r = i;
    (*tree)->n = size;
    return OK;
}
//销毁树
Status ParentTreeDestroy(PTree* tree){
    if(!tree)
        return ERROR;
    free(tree);
    return OK;
}
//获得结点的深度，未找到返回0
int ParentTreeNodeDepth(const PTree* tree, ElemType num){
    if(!tree || tree->n < 1)
        return ERROR;
    int i = 0;
    for(; i < tree->n; i++){//循环找到结点下标
        if(tree->nodes[i].data == num)
            break;
    }
    if(i == tree->n)//未找到
        return 0;
    int dep = 1;
    while(i != tree->r){//当找到根结点时结束
        i = tree->nodes[i].parent;
        dep++;
    }
    return dep;
}
//求树的高度
int ParentTreeDepth(const PTree* tree){
    if(!tree || tree->n < 0)
        return ERROR;
    if(tree->n == 0)//树长度为零
        return 0;
    int max = 1;//最大结点深度，即树的深度
    for(int i = 0; i < tree->n; i++){
        int dep = 1, j = i;
        while(j != tree->r){
            j = tree->nodes[j].parent;
            dep++;
        }
        max = max > dep ? max : dep;
    }
    return max;
}
//先根序遍历
Status ParentTreePreTraverse(const PTree* tree, Status (*visit)(ElemType*)){
    if(!tree || tree->n < 0 || !visit)
        return ERROR;
    if(tree->n == 0){
        printf("该树为空！\n");
        return OK;
    }
    return _ParentTreePreTraverse(tree, -1, visit);
}
//先根序遍历子函数， parent双亲下标
Status _ParentTreePreTraverse(const PTree* tree, int parent, Status (*visit)(ElemType*)){
    for(int i = 0; i < tree->n; i++){
        if(tree->nodes[i].parent == parent){//先操作后递归
            if(visit(&tree->nodes[i].data) != OK)//操作该结点
                return ERROR;
            _ParentTreePreTraverse(tree, i, visit);
        }
    }
    return OK;
}
//后根序遍历
Status ParentTreePostTraverse(const PTree* tree, Status (*visit)(ElemType*)){
    if(!tree || tree->n < 0 || !visit)
        return ERROR;
    if(tree->n == 0){
        printf("该树为空！\n");
        return OK;
    }
    return _ParentTreePostTraverse(tree, -1, visit);
}
//后根序遍历子函数，parent双亲结点
Status _ParentTreePostTraverse(const PTree* tree, int parent, Status (*visit)(ElemType*)){
    for(int i = 0; i < tree->n; i++){
        if(tree->nodes[i].parent == parent){//先递归后操作
            _ParentTreePostTraverse(tree, i, visit);
            if(visit(&tree->nodes[i].data) != OK)//操作该结点
                return ERROR;
        }
    }
    return OK;
}
//层次遍历
Status ParentTreeLevelTraverse(const PTree* tree, Status (*visit)(ElemType*)){
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
        for(int i = 0; i < tree->n; i++){//循环把该下标结点的子节点的下标装入队列
            if(tree->nodes[i].parent == index){
                queue[t++] = i;
            }
        }
        if(visit(&tree->nodes[index].data) != OK)//操作该结点
            return ERROR;
    }
    free(queue);
    return OK;
}
//根到节点的路径
Status ParentTreePath(const PTree* tree, ElemType num){
    if(!tree || tree->n <= 0)
        return ERROR;
    int i = 0;
    for(; i < tree->n; i++){//循环找到该结点下标
        if(tree->nodes[i].data == num)
            break;
    }
    if(i == tree->n)//未找到
        return 0;
    printf("（结点）%d <- ", num);
    i = tree->nodes[i].parent;
    while(i != tree->r){//当找到根结点结束循环
        printf("%d <- ", tree->nodes[i].data);
        i = tree->nodes[i].parent;
    }
    printf("（根）%d", tree->nodes[i].data);
}
//简单打印函数
Status ParentTreeVisit(ElemType* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
