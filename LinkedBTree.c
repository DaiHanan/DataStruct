#include "LinkedBTree.h"

//初始化二叉树
Status LinkedBTreeInit(LinkedBTree* tree){
    if(!tree)
        return ERROR;
    LinkedBTreeDestroy(*tree);//先释放空间
    *tree = NULL;
    return OK;
}
//创建二叉树，采用（先序）数组创建是为了Demo方便
Status LinkedBTreeCreateByNums(LinkedBTree* tree, int nums[], int len){
    if(!tree || !nums || len < 1)
        return ERROR;
    return _LinkedBTreeCreateByNums(tree, nums, len, 0);
}
//创建二叉树，采用（先序）数组创建是为了Demo方便   子函数
Status _LinkedBTreeCreateByNums(LinkedBTree* tree, int nums[], int len, int idx){
    if(idx >= len || nums[idx] <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (LinkedBTreeNode*)malloc(sizeof(LinkedBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = nums[idx];
    if(_LinkedBTreeCreateByNums(&((*tree)->left), nums, len, idx * 2 + 1) != OK)//递归左子树
        return OVERFLOW;
    if(_LinkedBTreeCreateByNums(&((*tree)->right), nums, len, idx * 2 + 2) != OK)//递归右子树
        return OVERFLOW;
    return OK;
}
//创建二叉树，动态创建
Status LinkedBTreeCreate(LinkedBTree* tree){
    if(!tree)
        return ERROR;
    LinkedBTreeInit(tree);//先释放原空间
    printf("根");
    return _LinkedBTreeCreate(tree);
}
//创建二叉树，动态创建子函数
Status _LinkedBTreeCreate(LinkedBTree* tree){
    int data;
    printf("结点：");
    scanf("%d", &data);
    if(data <= 0){//结点为空
        *tree = NULL;
        return OK;
    }
    *tree = (LinkedBTreeNode*)malloc(sizeof(LinkedBTreeNode));
    if(!*tree)
        return OVERFLOW;
    (*tree)->data = data;
    printf("左");
    if(_LinkedBTreeCreate(&((*tree)->left)) != OK)//创建左子树
        return OVERFLOW;
    printf("右");
    if(_LinkedBTreeCreate(&((*tree)->right)) != OK)//创建右子树
        return OVERFLOW;
    return OK;
}
//销毁二叉树
Status LinkedBTreeDestroy(LinkedBTree tree){
    if(!tree)
        return OK;
    LinkedBTreeDestroy(tree->left);//销毁左子树
    LinkedBTreeDestroy(tree->right);//销毁右子树
    free(tree);
    return OK;
}
//先序遍历二叉树
Status LinkedBTreePreTraverse(LinkedBTree tree, Status (*visit)(ElemType*)){
    if(!tree)
        return OK;
    visit(&tree->data);
    if(LinkedBTreePreTraverse(tree->left, visit) != OK)
        return ERROR;
    if(LinkedBTreePreTraverse(tree->right, visit) != OK)
        return ERROR;
    return OK;
}
//中序遍历二叉树
Status LinkedBTreeInTraverse(LinkedBTree tree, Status (*visit)(ElemType*)){
    if(!tree)
        return OK;
    if(LinkedBTreeInTraverse(tree->left, visit) != OK)
        return ERROR;
    visit(&tree->data);
    if(LinkedBTreeInTraverse(tree->right, visit) != OK)
        return ERROR;
    return OK;
}
//后序遍历二叉树
Status LinkedBTreePostTraverse(LinkedBTree tree, Status (*visit)(ElemType*)){
    if(!tree)
        return OK;
    if(LinkedBTreePostTraverse(tree->left, visit) != OK)
        return ERROR;
    if(LinkedBTreePostTraverse(tree->right, visit) != OK)
        return ERROR;
    visit(&tree->data);
    return OK;
}
//层次遍历二叉树
Status LinkedBTreeLevelTraverse(LinkedBTree tree, Status (*visit)(ElemType*)){
    if(!tree || !visit)
        return ERROR;
    //使用简易队列
    int front = 0, tail = 0;
    LinkedBTreeNode** queue = (LinkedBTreeNode**)
    malloc(sizeof(LinkedBTreeNode*) * LinkedBTreeLength(tree));//队列长度为tree长度
    if(!queue)
        return OVERFLOW;
    LinkedBTreeNode* p;
    queue[tail++] = tree;
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
int LinkedBTreeLength(const LinkedBTree tree){
    if(!tree)
        return 0;
    int len = 0;
    len += LinkedBTreeLength(tree->left);
    len += LinkedBTreeLength(tree->right);
    return len + 1;
}
//返回二叉树叶节点个数
int LinkedBTreeLeafCount(const LinkedBTree tree){
	if(!tree)
        return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 1;
    return LinkedBTreeLeafCount(tree->left) + LinkedBTreeLeafCount(tree->right);
}
//返回二叉树度为1的结点个数
int LinkedBTreeNode_1Count(const LinkedBTree tree){
	if(!tree)
        return 0;
    int len = 0;
    len += LinkedBTreeNode_1Count(tree->left);
    len += LinkedBTreeNode_1Count(tree->right);
	if(tree->left == NULL && tree->right != NULL || tree->left != NULL && tree->right == NULL)
		len++;
    return len;
}
//返回二叉树深度
int LinkedBTreeDepth(const LinkedBTree tree){
    if(!tree)
        return 0;
    int dep = 0;
    int left = LinkedBTreeDepth(tree->left);
    int right = LinkedBTreeDepth(tree->right);
    dep = left > right ? left : right;
    return dep + 1;
}
//返回二叉树带权路径长度 （WPL = weighted path length）
int LinkedBTreeWPL(const LinkedBTree tree){
    int wpl = 0;
    _LinkedBTreeWPL(tree, 1, &wpl);
    return wpl;
}
//返回二叉树带权路径长度子函数
int _LinkedBTreeWPL(const LinkedBTree tree, int dep, int* wpl){
    //static int wpl = 0;//不会因为递归而刷新，重复调用会翻倍！
    if(!tree)
        return;
    if(!tree->left && !tree->right)//叶子结点
        *wpl += tree->data * dep;
    _LinkedBTreeWPL(tree->left, dep + 1, wpl);
    _LinkedBTreeWPL(tree->right, dep + 1, wpl);
    return;
}
//打印根到某个节点的路径
Status LinkedBTreePath(const LinkedBTree tree, ElemType num){
    if(!tree || LinkedBTreeContain(tree, num) == FALSE)
        return ERROR;

    typedef struct{//临时结构体
        LinkedBTreeNode* node;//当前结点指针
        int parent;//存放双亲在队列中的位置
    }snode;

    //创建队列
    snode* Qu = (snode*)malloc(sizeof(snode) * LinkedBTreeLength(tree));
    if(!Qu)
        return OVERFLOW;

    int front = -1, rear = 0, curr;
    Qu[rear].node = tree;//根节点进入队列
    Qu[rear].parent = -1;//根节点没有双亲
    LinkedBTreeNode* node = tree;
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
        if(node->left){//左子树入队
            Qu[++rear].node = node->left;
            Qu[rear].parent = front;
        }
        if(node->right){//右子树入队
            Qu[++rear].node = node->right;
            Qu[rear].parent = front;
        }
    }
    free(Qu);
    return OK;
}
//打印根到所有叶子节点的路径
Status LinkedBTreeAllPath(const LinkedBTree tree){
	if(!tree)
		return ERROR;
	ElemType* path = (ElemType*)
		malloc(sizeof(ElemType)*LinkedBTreeDepth(tree));//临时数据数组内数据最大长度为数组深度
	if(!path)
		return OVERFLOW;
	_LinkedBTreeAllPath(tree, path, 0);
	free(path);
	return OK;
}
//打印根到所有叶子节点的路径子函数
void _LinkedBTreeAllPath(const LinkedBTree tree, ElemType path[], int len){
	if(!tree)
		return;
	path[len] = tree->data;//将当前结点数据放入path数组
	if(tree->left == NULL && tree->right == NULL){//叶子结点
		printf("（结点）");
		for(int i = len; i > 0; i--){//循环打印结点数据
			printf(" %d <-", path[i]);
		}
		printf("（根）%d\n", path[0]);//打印根结点数据
	}
	else{//递归
		_LinkedBTreeAllPath(tree->left, path, len + 1);
		_LinkedBTreeAllPath(tree->right, path, len + 1);
	}
	return;
}
//验证元素num是否在该树里
Status LinkedBTreeContain(const LinkedBTree tree, ElemType num){
    if(!tree)
        return FALSE;
    if(tree->data == num ||
       LinkedBTreeContain(tree->left, num) == TRUE ||
       LinkedBTreeContain(tree->right, num) == TRUE)
        return TRUE;
    return FALSE;
}
//简单打印函数
Status LinkedBTreeVisit(ElemType* num){
    if(!num)
        return ERROR;
    printf("%d ", *num);
    return OK;
}
//获得元素num所在结点指针
LinkedBTreeNode* LinkedBTreeGetNode(const LinkedBTree tree, ElemType num){
	if(!tree)
        return NULL;
    //使用简易队列
    int front = 0, tail = 0;
    LinkedBTreeNode** queue = (LinkedBTreeNode**)
    malloc(sizeof(LinkedBTreeNode*) * LinkedBTreeLength(tree));//队列长度为tree长度
    if(!queue)
        return NULL;
    LinkedBTreeNode* p;
    queue[tail++] = tree;
    while(tail != front){
        p = queue[front++];
        if(p->data == num)
			return p;
        if(p->left)
            queue[tail++] = p->left;//左子树入队
        if(p->right)
            queue[tail++] = p->right;//右子树入队
    }
    free(queue);
    return NULL;
}
//交换二叉树所有结点的左右结点
Status LinkedBTreeReverseNode(LinkedBTree tree){
	if(!tree)//树为空直接返回
		return OK;
    //交换
    LinkedBTree p = tree->left;
	tree->left = tree->right;
	tree->right = p;
    //递归
	LinkedBTreeReverseNode(tree->left);
	LinkedBTreeReverseNode(tree->right);
	return OK;
}
