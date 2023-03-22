#include "Search.h"

//顺序查找
int SearchSeq(ElemType nums[], int size, ElemType elem){
    for(int i = 0; i < size; i++)
        if(nums[i] == elem)
            return i;
    return -1;
}
//折半查找 条件：升序数组
int SearchBise(ElemType nums[], int size, ElemType elem){
    int l = 0, r = size - 1;
    while(l <= r){
        int mid = (l + r) / 2;
        if(nums[mid] == elem)
            return mid;
        if(nums[mid] < elem)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

//次优查找树
//次优查找树查找，设元素的权值为元素大小
ElemType SearchSecondOptimalTree(ElemType nums[], int size, ElemType elem){
    if(!nums, size < 1)
        return -1;
    LinkedBTree tree = NULL;
    //创建sw(累计权值表)
    ElemType sw[MAXSIZE] = {0};
    for(int i = 1; i < size; i++)
        sw[i] = sw[i - 1] + nums[i];
    //创建查找树
    _SearchSecondOptimalTree_create(&tree, nums, sw, 1, size - 1);
    //查找元素
    ElemType res = -1;
    _SearchSecondOptimalTree_find(tree, elem, &res);
    return res;
}
//次优查找树查找 子函数 创建次优二叉树
void _SearchSecondOptimalTree_create(LinkedBTree* tree, ElemType nums[], ElemType sw[], int left, int right){
    //指向p最小的值
    ElemType min = abs(sw[left] - sw[right]);
    ElemType dw = sw[right] + sw[left - 1];//sw[0] = 0
    int i = left;
    for(int j = left + 1; j <= right; j++)
        if(abs(dw - sw[j] - sw[j - 1]) < min){
            i = j;
            min = abs(dw - sw[j] - sw[j - 1]);
        }
    *tree = (LinkedBTree)malloc(sizeof(LinkedBTreeNode));
    (*tree)->data = nums[i];

    //左
    if(i == left)
        (*tree)->left = NULL;
    else
        _SearchSecondOptimalTree_create(&((*tree)->left), nums, sw, left, i - 1);
    //右
    if(i == right)
        (*tree)->right = NULL;
    else
        _SearchSecondOptimalTree_create(&((*tree)->right), nums, sw, i + 1, right);
}
//次优查找树查找 子函数 递归查找
void _SearchSecondOptimalTree_find(LinkedBTree tree, ElemType num, ElemType* p){
    if(!tree)
        return;
    if(num == tree->data){
        *p = tree->data;
        return;
    }
    if(num < tree->data)//递归左树
        _SearchSecondOptimalTree_find(tree->left, num, p);
    else//递归右树
        _SearchSecondOptimalTree_find(tree->right, num, p);
}

//二叉查找树
//创建
Status BinTreeCreate(LinkedBTree* tree){
    //先清空内存
    LinkedBTree p = *tree;
    while(p){
        BinTreeDelete(&p, p->data);
    }
    //重置指针
    *tree = NULL;
}
//查找，找到了就用指针p返回
Status BinTreeFind(LinkedBTree tree, ElemType elem, LinkedBTree f, LinkedBTree* p){
    if(!tree){
        *p = f;
        return FALSE;
    }
    if(elem == tree->data){
        *p = tree;
        return TRUE;
    }
    if(elem < tree->data)
        return BinTreeFind(tree->left, elem, tree, p);
    return BinTreeFind(tree->right, elem, tree, p);
}
//插入
Status BinTreeInsert(LinkedBTree* tree, ElemType elem){
    LinkedBTree p = NULL;
    if(BinTreeFind(*tree, elem, NULL, &p) != FALSE)
        return ERROR;
    //不存在elem才插入
    //创建新结点
    LinkedBTree newNode = (LinkedBTree)malloc(sizeof(LinkedBTreeNode));
    if(!newNode)//申请内存失败
        return OVERFLOW;
    newNode->data = elem;
    newNode->left = newNode->right = NULL;

    if(!p)//根结点
        *tree = newNode;
    else if(elem < p->data)//插入左树
        p->left = newNode;
    else//插入右树
        p->right = newNode;
    return OK;
}
//删除
Status BinTreeDelete(LinkedBTree* tree, ElemType elem){
    if(!*tree)
        return ERROR;
    if(elem == (*tree)->data)//找到进行删除
        return _BinTreeDelete(tree);
    if(elem < (*tree)->data)//递归左树
        return BinTreeDelete(&(*tree)->left, elem);
    else//递归右树
        return BinTreeDelete(&(*tree)->right, elem);
}
//删除 子函数
Status _BinTreeDelete(LinkedBTree* tree){
    LinkedBTree q = *tree, s;
    //如果没有左树，只接右树
    if(!(*tree)->left){
        *tree = (*tree)->right;
        free(q);
    }
    //如果没有右树，只接左树
    else if(!(*tree)->right){
        *tree = (*tree)->left;
        free(q);
    }
    //左右都有
    else{
        //找到tree的前驱
        s = (*tree)->left;
        while(s->right){
            q = s;
            s = s->right;
        }
        //更换数据
        (*tree)->data = s->data;
        //重设q的指针
        if(q != *tree)
            q->right = s->left;
        else
            q->left = s->left;

        free(s);
    }
    return OK;
}
//平均查找长度
float BinTreeASL(LinkedBTree tree){
    if(!tree)
        return 0;
    int count = 0;
    float ASL = _BinTreeASL(tree, 1, &count);
    return ASL / count;
}
//平均查找长度 子函数
int _BinTreeASL(LinkedBTree tree, int dep, int* count){
    if(!tree)
        return 0;
    //获得元素个数
    *count += 1;
    //累加ASL
    int ASL = 0;
    ASL += dep;
    ASL += _BinTreeASL(tree->left, dep + 1, count);
    ASL += _BinTreeASL(tree->right, dep + 1, count);
    return ASL;
}


//二叉平衡树
//左旋
Status AVLTreeLRotate(AVLTree* t){
    AVLTree p = (*t)->right;
    (*t)->right = p->left;
    p->left = (*t);
    (*t) = p;
}
//右旋
Status AVLTreeRRotate(AVLTree* t){
    AVLTree p = (*t)->left;
    (*t)->left = p->right;
    p->right = (*t);
    (*t) = p;
}
//左平衡
Status AVLTreeLBalance(AVLTree* t){
    AVLTree l, lr;
    l = (*t)->left;
    switch(l->bf){
    case LH:
        (*t)->bf = l->bf = EH;
        AVLTreeRRotate(t);//右旋
        break;
    case RH:
        lr = l->right;
        switch(lr->bf){
        case LH:
            (*t)->bf = RH;
            l->bf = EH;
            break;
        case EH:
            (*t)->bf = l->bf = EH;
            break;
        case RH:
            (*t)->bf = EH;
            l->bf = LH;
            break;
        }
        lr->bf = EH;
        //先对左子树左旋再对根右旋
        AVLTreeLRotate(&((*t)->left));
        AVLTreeRRotate(t);
    }
}
//右平衡
Status AVLTreeRBalance(AVLTree* t){
    AVLTree r, rl;
    r = (*t)->right;
    switch(r->bf){
    case RH:
        (*t)->bf = r->bf = EH;
        AVLTreeLRotate(t);//左旋
        break;
    case LH:
        rl = r->left;
        switch(rl->bf){
        case RH:
            (*t)->bf = LH;
            r->bf = EH;
            break;
        case EH:
            (*t)->bf = r->bf = EH;
            break;
        case LH:
            (*t)->bf = EH;
            r->bf = RH;
            break;
        }
        rl->bf = EH;
        //先对右子树右旋再对根左旋
        AVLTreeRRotate(&((*t)->left));
        AVLTreeLRotate(t);
    }
}
//插入
Status AVLTreeInsert(AVLTree* t, ElemType elem, Status* taller){
    if(!*t){//插入新节点
        *t = (AVLTree)malloc(sizeof(AVLTreeNode));
        (*t)->data = elem;
        (*t)->left = (*t)->right = NULL;
        (*t)->bf = EH;
        *taller = TRUE;
    }
    else{
        if(elem == (*t)->data){//已存在，不再插入
            *taller = FALSE;
            return FALSE;
        }
        if(elem < (*t)->data){
            //左子树搜索
            if(!AVLTreeInsert(&(*t)->left, elem, taller))//未插入
                return FALSE;
            if(*taller == TRUE){//已插入
                switch((*t)->bf){
                case LH://原左高，需左平衡
                    AVLTreeLBalance(t);
                    *taller = FALSE;
                    break;
                case EH://原等高，树增高
                    (*t)->bf = LH;
                    *taller = TRUE;
                    break;
                case RH://原右高，现等高
                    (*t)->bf = EH;
                    *taller = FALSE;
                    break;
                }
            }
        }
        else{
            //右子树搜索
            if(!AVLTreeInsert(&(*t)->right, elem, taller))//未插入
                return FALSE;
            if(*taller == TRUE){//已插入
                switch((*t)->bf){
                case RH://原右高，需右平衡
                    AVLTreeRBalance(t);
                    *taller = FALSE;
                    break;
                case EH://原等高，树增高
                    (*t)->bf = LH;
                    *taller = TRUE;
                    break;
                case LH://原左高，现等高
                    (*t)->bf = EH;
                    *taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}
//查找，找到用指针p返回
Status AVLTreeFind(AVLTree t, ElemType elem, AVLTree* p){
    if(!t)
        return ERROR;
    if(elem == t->data){
        *p = t;
        return OK;
    }
    if(elem < t->data)
        return AVLTreeFind(t->left, elem, p);
    return AVLTreeFind(t->right, elem, p);
}


//打印
Status SearchPrint(ElemType nums[], int size){
    for(int i = 0; i < size; i++)
        printf("%d ", nums[i]);
    printf("\n");
}
