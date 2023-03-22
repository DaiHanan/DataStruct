#include "Test.h"
//线性表用例
ElemType nums[10] = {1, 4, 3, 6, 8, 2, 9, 5, 0, 10};
//二叉树的完全二叉树用例
int treeNums[] = {1, 2, 3, 4, 5, 6};
//图的邻接矩阵（有向图）用例
int graphNums[] = {0, 1, 2, 3, 4};
EdgeType AdjMatrix[][5] = {
    {0, 9, INT_MAX, INT_MAX, 20},
    {INT_MAX, 0, 3, INT_MAX, INT_MAX},
    {2, INT_MAX, 0, 5, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 0, 1},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0},
};

void test(){
    //线性表
    //SeqListDemo();
    //LinkedListDemo();
    //DoublyLinkedListDemo();
    //LoopLinkedListDemo();
    //栈
    //SeqStackDemo();
    //LinkedStackDemo();
    //队列
    //SeqQueueDemo();
    //LinkedQueueDemo();
    //串
    //StaticStrDemo();
    //DynamicStrDemo();
    //LinkedStrDemo();
    //矩阵
    //ArrayDemo();
    //TSMatrixDemo();
    //RLSMatrixDemo();
    //OLSMatrixDemo();
    //广义表
    //SubGListDemo();
    //LinkedGListDemo();
    //二叉树
    //SeqBTreeDemo();
    //LinkedBTreeDemo();
    //TLinkedBTreeDemo();
    //ThreadBTreeDemo();
    //HuffManBTreeDemo();
    //树
    //ParentTreeDemo();
    //ChildTreeDemo();
    //CSTreeDemo();
    //图
    AdjMatrixGraphDemo();
    //AdjListGraphDemo();
    //InverseAdjListGraphDemo();
    //OLGraphDemo();
    //AdjMultilistGraphDemo();
    //查找
    //SearchDemo();
    //HashTableDemo();
    //排序
    //SortDemo();
}

//顺序表
void SeqListDemo(){
    SeqList* list = NULL;
    SeqListInit(&list);
    SeqListOutput(list);
    for(int i = 0; i < 10; i++){
        SeqListInsert(list, i + 1, nums[i]);
    }
    SeqListOutput(list);

    ElemType elem;
    SeqListGetElem(list, 4, &elem);
    printf("元素%d的位置是：%d\n", elem, SeqListLocateElem(list, elem));

    printf("\n删除元素：");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        SeqListDelete(list, rand() % SeqListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\n剩下元素：\n");
    SeqListOutput(list);
    SeqListDestroy(list);
    list = NULL;
}
//链式表
void LinkedListDemo(){
    LinkedList* list = NULL;
    LinkedListInit(&list);
    LinkedListTraverse(list, LinkedListVisit);
    for(int i = 0; i < 10; i++){
        LinkedListInsert(list, i + 1, nums[i]);
    }
    LinkedListTraverse(list, LinkedListVisit);

    ElemType elem;
    LinkedListGetElem(list, 2, &elem);
    printf("元素%d的位置是：%d\n", elem, LinkedListLocateElem(list, elem));

    printf("\n删除元素：");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        LinkedListDelete(list, rand() % LinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\n剩下元素：\n");
    LinkedListTraverse(list, LinkedListVisit);
    LinkedListDestroy(list);
    list = NULL;
}
//双向链表
void DoublyLinkedListDemo(){
    DoublyLinkedList* list = NULL;
    DoublyLinkedListInit(&list);
    DoublyLinkedListTraverse(list, DoublyLinkedListVisit);
    for(int i = 0; i < 10; i++){
        DoublyLinkedListInsert(list, i + 1, nums[i]);
    }
    DoublyLinkedListTraverse(list, DoublyLinkedListVisit);

    dNode* node1, * node2;
    DoublyLinkedListGetNode(list, 8, &node1);
    node2 = DoublyLinkedListGetPreNode(list, node1, 3);
    printf("结点元素 %d 的前面第三个结点元素为 %d\n", node1->data, node2->data);

    ElemType elem;
    DoublyLinkedListGetElem(list, 7, &elem);
    printf("元素%d的位置是：%d\n", elem, DoublyLinkedListLocateElem(list, elem));

    printf("\n删除元素：");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        DoublyLinkedListDelete(list, rand() % DoublyLinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\n剩下元素：\n");
    DoublyLinkedListTraverse(list, DoublyLinkedListVisit);
    DoublyLinkedListDestroy(list);
    list = NULL;
}
//循环链表
void LoopLinkedListDemo(){
    LoopLinkedList* list = NULL;
    LoopLinkedListInit(&list);
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);
    for(int i = 0; i < 10; i++){
        LoopLinkedListInsert(list, i + 1, nums[i]);
    }
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);

    printf("\n从第%d个元素开始遍历：\n", 3);
    LoopLinkedListTraverse(list, 3, LoopLinkedListVisit);

    ElemType elem;
    LoopLinkedListGetElem(list, 7, &elem);
    printf("\n元素%d的位置是：%d\n", elem, LoopLinkedListLocateElem(list, elem));

    printf("\n删除元素：");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        LoopLinkedListDelete(list, rand() % LoopLinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\n剩下元素：\n");
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);
    LoopLinkedListDestroy(list);
    list = NULL;
}
//顺序栈
void SeqStackDemo(){
    SeqStack* stack = NULL;
    SeqStackInit(&stack);
    SeqStackTraverse(stack, SeqStackVisit);
    for(int i = 0; i < 10; i++){
        SeqStackPush(stack, nums[i]);
    }
    SeqStackTraverse(stack, SeqStackVisit);

    ElemType elem = 4;
    printf("元素%d的位置是：%d\n", elem, SeqStackLocateElem(stack, elem));

    printf("\n删除元素：");
    for(int i = 0; i < 4; i++){
        SeqStackPop(stack, &elem);
        printf("%d ", elem);
    }
    SeqStackTop(stack, &elem);
    printf("\n此时栈顶元素：%d\n", elem);
    printf("剩下元素：\n");
    SeqStackTraverse(stack, SeqStackVisit);
    SeqStackDestroy(stack);
    stack = NULL;
}
//链式栈
void LinkedStackDemo(){
    LinkedStack* stack = NULL;
    LinkedStackInit(&stack);
    LinkedStackTraverse(stack, LinkedStackVisit);
    for(int i = 0; i < 10; i++){
        LinkedStackPush(stack, nums[i]);
    }
    LinkedStackTraverse(stack, LinkedStackVisit);

    ElemType elem = 4;
    printf("元素%d的位置是：%d\n", elem, LinkedStackLocateElem(stack, elem));

    printf("\n删除元素：");
    for(int i = 0; i < 4; i++){
        LinkedStackPop(stack, &elem);
        printf("%d ", elem);
    }
    LinkedStackTop(stack, &elem);
    printf("\n此时栈顶元素：%d\n", elem);
    printf("剩下元素：\n");
    LinkedStackTraverse(stack, LinkedStackVisit);
    LinkedStackDestroy(stack);
    stack = NULL;
}
//顺序队列
void SeqQueueDemo(){
    SeqQueue* queue = NULL;
    SeqQueueInit(&queue);
    SeqQueueTraverse(queue, SeqQueueVisit);
    for(int i = 0; i < 10; i++){
        SeqQueuePush(queue, nums[i]);
    }
    SeqQueueTraverse(queue, SeqQueueVisit);

    ElemType elem = 5;
    printf("元素%d的位置是：%d\n", elem, SeqQueueLocateElem(queue, elem));

    printf("\n删除元素：");
    for(int i = 0; i < 4; i++){
        SeqQueuePop(queue, &elem);
        printf("%d ", elem);
    }
    SeqQueueTop(queue, &elem);
    printf("\n此时栈顶元素：%d\n", elem);
    printf("剩下元素：\n");
    SeqQueueTraverse(queue, SeqQueueVisit);
    SeqQueueDestroy(queue);
    queue = NULL;
}
//链式队列
void LinkedQueueDemo(){
    LinkedQueue* queue = NULL;
    LinkedQueueInit(&queue);
    LinkedQueueTraverse(queue, LinkedQueueVisit);
    for(int i = 0; i < 10; i++){
        LinkedQueuePush(queue, nums[i]);
    }
    LinkedQueueTraverse(queue, LinkedQueueVisit);

    ElemType elem = 8;
    printf("元素%d的位置是：%d\n", elem, LinkedQueueLocateElem(queue, elem));

    printf("\n删除元素：");
    for(int i = 0; i < 4; i++){
        LinkedQueuePop(queue, &elem);
        printf("%d ", elem);
    }
    LinkedQueueTop(queue, &elem);
    printf("\n此时栈顶元素：%d\n", elem);
    printf("剩下元素：\n");
    LinkedQueueTraverse(queue, LinkedQueueVisit);
    LinkedQueueDestroy(queue);
    queue = NULL;
}
//静态串
void StaticStrDemo(){
    StaticStr* str1 = NULL;
    StaticStrInit(&str1);
    StaticStrPrint(str1);
    StaticStrAssign(str1, "122");
    StaticStrPrint(str1);
    printf("长度为：%d\n", StaticStrLength(str1));

    StaticStr* str2 = NULL;
    StaticStrInit(&str2);
    StaticStrAssign(str2, "452");

    StaticStrCopy(str1, str2);
    printf("\n拷贝后：\n");
    StaticStrPrint(str1);

    StaticStr* str3 = NULL;
    StaticStrInit(&str3);
    StaticStrAssign(str3, "782");
    printf("\n连接后：\n");
    StaticStrConcat(str1, str2, str3);
    StaticStrPrint(str1);

    printf("\nstr1 : ");
    StaticStrPrint(str1);
    printf("str3 : ");
    StaticStrPrint(str3);
    printf("str1 ");
    if(StaticStrCompare(str1, str3) < 0)
        printf("小于");
    else
        printf("大于等于");
    printf(" str3\n");

    StaticStrInsert(str1, str3, 2);
    printf("\nstr3插入str1的第2个位置后，str1 为：\n");
    StaticStrPrint(str1);

    StaticStrDelete(str1, 2, 2);
    printf("\n删除str1中第 2 个位置开始长为 2 的子串后，str1 为：\n");
    StaticStrPrint(str1);

    StaticStrSubStr(str2, str1, 2, 4);
    printf("\nstr1中从位置 2 开始长度为 4 的子串为：\n");
    StaticStrPrint(str2);

    printf("\nstr1 为：\n");
    StaticStrPrint(str1);
    StaticStrAssign(str2, "2");
    StaticStrAssign(str3, "AAA");
    StaticStrReplace(str1, str2, str3);
    printf("用\' AAA \'替换str1中所有的\'2\'后，\nstr1 为：\n");
    StaticStrPrint(str1);
    StaticStrDestroy(str1);
    StaticStrDestroy(str2);
    StaticStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//动态串
void DynamicStrDemo(){
    DynamicStr* str1 = NULL;
    DynamicStrInit(&str1);
    DynamicStrPrint(str1);
    DynamicStrAssign(str1, "112");
    DynamicStrPrint(str1);
    printf("长度为：%d\n", DynamicStrLength(str1));

    DynamicStr* str2 = NULL;
    DynamicStrInit(&str2);
    DynamicStrAssign(str2, "156");

    DynamicStrCopy(str1, str2);
    printf("\n拷贝后：\n");
    DynamicStrPrint(str1);

    DynamicStr* str3 = NULL;
    DynamicStrInit(&str3);
    DynamicStrAssign(str3, "189");
    printf("\n连接后：\n");
    DynamicStrConcat(str1, str2, str3);
    DynamicStrPrint(str1);

    printf("\nstr1 : ");
    DynamicStrPrint(str1);
    printf("str3 : ");
    DynamicStrPrint(str3);
    printf("str1 ");
    if(DynamicStrCompare(str1, str3) < 0)
        printf("小于");
    else
        printf("大于等于");
    printf(" str3\n");

    DynamicStrInsert(str1, str3, 2);
    printf("\nstr3插入str1的第2个位置后，str1 为：\n");
    DynamicStrPrint(str1);

    DynamicStrDelete(str1, 2, 2);
    printf("\n删除str1中第 2 个位置开始长为 2 的子串后，str1 为：\n");
    DynamicStrPrint(str1);

    DynamicStrSubStr(str2, str1, 2, 4);
    printf("\nstr1中从位置 2 开始长度为 4 的子串为：\n");
    DynamicStrPrint(str2);

    printf("\nstr1 为：\n");
    DynamicStrPrint(str1);
    DynamicStrAssign(str2, "1");
    DynamicStrAssign(str3, "AAA");
    DynamicStrReplace(str1, str2, str3);
    printf("用\' AAA \'替换str1中所有的\'1\'后，\nstr1 为：\n");
    DynamicStrPrint(str1);
    DynamicStrDestroy(str1);
    DynamicStrDestroy(str2);
    DynamicStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//块链串
void LinkedStrDemo(){
    LinkedStr* str1 = NULL;
    LinkedStrInit(&str1);
    LinkedStrPrint(str1);
    LinkedStrAssign(str1, "123");
    LinkedStrPrint(str1);
    printf("长度为：%d\n", LinkedStrLength(str1));

    LinkedStr* str2 = NULL;
    LinkedStrInit(&str2);
    LinkedStrAssign(str2, "406");

    LinkedStrCopy(str1, str2);
    printf("\n拷贝后：\n");
    LinkedStrPrint(str1);

    LinkedStr* str3 = NULL;
    LinkedStrInit(&str3);
    LinkedStrAssign(str3, "709");
    printf("\n连接后：\n");
    LinkedStrConcat(str1, str2, str3);
    LinkedStrPrint(str1);

    printf("\nstr1 : ");
    LinkedStrPrint(str1);
    printf("str3 : ");
    LinkedStrPrint(str3);
    printf("str1 ");
    if(LinkedStrCompare(str1, str3) < 0)
        printf("小于");
    else
        printf("大于等于");
    printf(" str3\n");

    LinkedStrInsert(str1, str3, 2);
    printf("\nstr3插入str1的第2个位置后，str1 为：\n");
    LinkedStrPrint(str1);

    LinkedStrDelete(str1, 2, 2);
    printf("\n删除str1中第 2 个位置开始长为 2 的子串后，str1 为：\n");
    LinkedStrPrint(str1);

    LinkedStrSubStr(str2, str1, 2, 4);
    printf("\nstr1中从位置 2 开始长度为 4 的子串为：\n");
    LinkedStrPrint(str2);

    printf("\nstr1 为：\n");
    LinkedStrPrint(str1);
    LinkedStrAssign(str2, "0");
    LinkedStrAssign(str3, "AAA");
    LinkedStrReplace(str1, str2, str3);
    printf("用\' AAA \'替换str1中所有的\'0\'后，\nstr1 为：\n");
    LinkedStrPrint(str1);

    LinkedStrDestroy(str1);
    LinkedStrDestroy(str2);
    LinkedStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//数组
void ArrayDemo(){
    Array* A = NULL;
    int ii = 3, jj = 3, kk = 2;
    int temp = 1;
    ArrayInit(&A, 3, ii, jj, kk);
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            for(int k = 0; k < kk; k++){
                ArrayAssign(A, i * 100 + j * 10 + k, i, j, k);
                ArrayValue(A, &temp, i, j, k);
                printf("%-3d ", temp);
            }
            printf("\n");
        }
        printf("\n");
    }
    Array* B = NULL;
    ArrayInit(&B, 3, 6, 6, 6);
    ArrayCopy(B, A);
    ArrayValue(B, &temp, 1, 1, 0);
    printf("复制数组的下标为1 1 0 的元素为 :%-3d\n", temp);
    ArrayDestroy(A);
    ArrayDestroy(B);
    A = B = NULL;
}
//三元组稀疏矩阵
void TSMatrixDemo(){
    TSMatrix* A = NULL;
    int ii = 3, jj = 3;
    int temp = 1;
    TSMatrixInit(&A, ii, jj);
    printf("初始化矩阵\n");
    TSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            TSMatrixAssign(A, i * 12 + j, i, j);
        }
    }
    TSMatrixPrint(A);

    printf("\n删除非零元（1,1）\n");
    TSMatrixAssign(A, 0, 1, 1);
    TSMatrixPrint(A);

    printf("\n增加非零元（1,1）\n");
    TSMatrixAssign(A, 99, 1, 1);
    TSMatrixPrint(A);

    printf("\n改变非零元（1,1）\n");
    TSMatrixAssign(A, 66, 1, 1);
    TSMatrixPrint(A);
    printf("\n");

    TSMatrix* B = NULL;
    TSMatrixInit(&B, 6, 6);
    TSMatrixCopy(B, A);
    TSMatrixValue(A, &temp, 2, 1);
    printf("原来矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    TSMatrixValue(B, &temp, 2, 1);
    printf("复制矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    TSMatrixDestroy(A);
    TSMatrixDestroy(B);
    A = B = NULL;
}
//行逻辑链接稀疏矩阵
void RLSMatrixDemo(){
    RLSMatrix* A = NULL;
    int ii = 3, jj = 3;
    int temp = 1;
    RLSMatrixInit(&A, ii, jj);
    printf("初始化矩阵\n");
    RLSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            RLSMatrixAssign(A, i * 12 + j, i, j);
        }
    }
    RLSMatrixPrint(A);

    printf("\n删除非零元（1,0）（1,1）\n");
    RLSMatrixAssign(A, 0, 1, 0);
    RLSMatrixAssign(A, 0, 1, 1);
    RLSMatrixPrint(A);

    printf("\n增加非零元（1,1）\n");
    RLSMatrixAssign(A, 99, 1, 1);
    RLSMatrixPrint(A);

    printf("\n改变非零元（1,1）\n");
    RLSMatrixAssign(A, 66, 1, 1);
    RLSMatrixPrint(A);
    printf("\n");

    int col = 0;
    RLSMatrixGetLineFirstElem(A, 1, &col);
    printf("第2行的第一个非零元下标为：%d\n", col);
    printf("\n");

    RLSMatrix* B = NULL;
    RLSMatrixInit(&B, 6, 6);
    RLSMatrixCopy(B, A);
    RLSMatrixValue(A, &temp, 2, 1);
    printf("原来矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    RLSMatrixValue(B, &temp, 2, 1);
    printf("复制矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    RLSMatrixDestroy(A);
    RLSMatrixDestroy(B);
    A = B = NULL;
}
//十字链表稀疏矩阵
void OLSMatrixDemo(){
    OLSMatrix* A = NULL;
    int ii = 5, jj = 4;
    int temp = 1;
    OLSMatrixInit(&A, ii, jj);
    printf("初始化矩阵\n");
    OLSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            if(OLSMatrixAssign(A, i * 12 + j, i, j) != OK)
                return ERROR;
        }
    }
    OLSMatrixPrint(A);

    printf("\n删除非零元（2,2）\n");
    OLSMatrixAssign(A, 0, 2, 2);
    OLSMatrixPrint(A);

    printf("\n增加非零元（2,2）\n");
    OLSMatrixAssign(A, 99, 2, 2);
    OLSMatrixPrint(A);

    printf("\n改变非零元（2,2）\n");
    OLSMatrixAssign(A, 66, 2, 2);
    OLSMatrixPrint(A);
    printf("\n");

    OLSMatrix* B = NULL;
    OLSMatrixInit(&B, 6, 6);
    OLSMatrixCopy(B, A);
    OLSMatrixValue(A, &temp, 2, 1);
    printf("原来矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    OLSMatrixValue(B, &temp, 2, 1);
    printf("复制矩阵的下标为2 1 的元素为 :%-3d\n", temp);
    OLSMatrixDestroy(A);
    OLSMatrixDestroy(B);
    A = B = NULL;
}
//子表广义表
void SubGListDemo(){
    SubGList L = NULL;
    SubGListInit(&L);
    StaticStr* S = NULL;
    StaticStrInit(&S);
    StaticStrAssign(S, "(a,(b),c,(d,(e)))");
    SubGListCreate(&L, S);
    printf("广义表赋值字符串为：\n");
    StaticStrPrint(S);
    printf("\n打印原表：\n");
    SubGListTraverse(&L, SubGListVisit);

    printf("\n\n表的长度为：%d\n", SubGListLength(&L));
    printf("表的深度为：%d\n", SubGListDepth(&L));

    SubGList T = NULL;
    SubGListInit(&T);
    SubGListCopy(&T, &L);
    printf("\n打印复制表：\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListGetHead(&T, &L);
    printf("\n\n打印表头：\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListGetTail(&T, &L);
    printf("\n打印表尾：\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListDestroy(&T);
    T = NULL;
    StaticStrAssign(S, "(f,(g))");
    SubGListCreate(&T, S);
    printf("\n\n添加新表头(f,(g))\n");
    SubGListInsertHead(&L, &T);
    printf("打印原表：\n");
    SubGListTraverse(&L, SubGListVisit);

    printf("\n\n删除表头\n");
    SubGListDeleteHead(&L, &T);
    printf("打印原表：\n");
    SubGListTraverse(&L, SubGListVisit);
    SubGListDestroy(&L);
    SubGListDestroy(&T);
    L = T = NULL;
}
//链式广义表
void LinkedGListDemo(){
	LinkedGList L = NULL;
    LinkedGListInit(&L);
    StaticStr* S = NULL;
    StaticStrInit(&S);

    StaticStrAssign(S, "(a,(b),c,(d,(e)))");
    LinkedGListCreate(&L, S);
    printf("广义表赋值字符串为：\n");
    StaticStrPrint(S);
    printf("\n打印原表：\n");
    LinkedGListTraverse(&L, LinkedGListVisit);


    printf("\n\n表的长度为：%d\n", LinkedGListLength(&L));
    printf("表的深度为：%d\n", LinkedGListDepth(&L));

    LinkedGList T = NULL;
    LinkedGListInit(&T);//该句可以不要
    LinkedGListCopy(&T, &L);
    printf("\n打印复制表：\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListGetHead(&T, &L);
    printf("\n\n打印表头：\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListGetTail(&T, &L);
    printf("\n打印表尾：\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListDestroy(&T);
    T = NULL;
    StaticStrAssign(S, "(f,(g))");
    LinkedGListCreate(&T, S);
    printf("\n\n添加新表头(f,(g))\n");
    LinkedGListInsertHead(&L, &T);
    printf("打印原表：\n");
    LinkedGListTraverse(&L, LinkedGListVisit);

    printf("\n\n删除表头\n");
    LinkedGListDeleteHead(&L, &T);
    printf("打印原表：\n");
    LinkedGListTraverse(&L, LinkedGListVisit);

    LinkedGListDestroy(&L);
    LinkedGListDestroy(&T);
    L = T = NULL;
}
//顺序二叉树
void SeqBTreeDemo(){
    printf("二叉树图如下：\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    SeqBTree tree;
    SeqBTreeInit(tree);
    //SeqBTreeCreate(tree);
    SeqBTreeCreateByNums(tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n先序遍历\n");
    SeqBTreePreTraverse(tree, SeqBTreeVisit);
    printf("\n中序遍历\n");
    SeqBTreeInTraverse(tree, SeqBTreeVisit);
    printf("\n后序遍历\n");
    SeqBTreePostTraverse(tree, SeqBTreeVisit);
    printf("\n层次遍历\n");
    SeqBTreeLevelTraverse(tree, SeqBTreeVisit);

    printf("\n\n长度为：%d\n", SeqBTreeLength(tree));
    printf("深度为：%d\n", SeqBTreeDepth(tree));
    printf("带权路径长度为：%d\n", SeqBTreeWPL(tree));

    printf("\n\'5\'是否在该表中： ");
    SeqBTreeContain(tree, 5) == TRUE ? printf("是") : printf("否");
    printf("\n\n从根\'1\'到\'5\'的路径为：\n");
    SeqBTreePath(tree, 5);
}
//二叉链式二叉树
void LinkedBTreeDemo(){
    printf("二叉树图如下：\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    LinkedBTree tree = NULL;
    //LinkedBTreeCreate(&tree);
    LinkedBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n先序遍历\n");
    LinkedBTreePreTraverse(tree, LinkedBTreeVisit);
    printf("\n中序遍历\n");
    LinkedBTreeInTraverse(tree, LinkedBTreeVisit);
    printf("\n后序遍历\n");
    LinkedBTreePostTraverse(tree, LinkedBTreeVisit);
    printf("\n层次遍历\n");
    LinkedBTreeLevelTraverse(tree, LinkedBTreeVisit);

    printf("\n\n长度为：%d\n", LinkedBTreeLength(tree));
    printf("深度为：%d\n", LinkedBTreeDepth(tree));
    printf("带权路径长度为：%d\n", LinkedBTreeWPL(tree));
	printf("叶子结点个数为：%d\n", LinkedBTreeLeafCount(tree));
	printf("度为1的结点个数为：%d\n", LinkedBTreeNode_1Count(tree));

    printf("\n\'5\'是否在该表中： ");
    LinkedBTreeContain(tree, 5) == TRUE ? printf("是") : printf("否");

    printf("\n\n从\'5\'到根\'1\'的路径为：\n");
    LinkedBTreePath(tree, 5);

	printf("\n\n所有叶子结点到根的路径为：\n");
    LinkedBTreeAllPath(tree);

	LinkedBTreeNode* p = LinkedBTreeGetNode(tree, 6);
	if(p)
		printf("\n\n获得结点\'6\'并打印该结点的数据：%d\n", p->data);

    printf("\n交换所有结点的左右结点之后先序遍历该树：\n");
    LinkedBTreeReverseNode(tree);
    LinkedBTreePreTraverse(tree, LinkedBTreeVisit);

	printf("\n");
    LinkedBTreeDestroy(tree);
    tree = NULL;
}

//三叉链式二叉树
void TLinkedBTreeDemo(){
    printf("二叉树图如下：\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    TLinkedBTree tree = NULL;
    //TLinkedBTreeCreate(&tree);
    TLinkedBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n先序遍历\n");
    TLinkedBTreePreTraverse(tree, TLinkedBTreeVisit);
    printf("\n中序遍历\n");
    TLinkedBTreeInTraverse(tree, TLinkedBTreeVisit);
    printf("\n后序遍历\n");
    TLinkedBTreePostTraverse(tree, TLinkedBTreeVisit);
    printf("\n层次遍历\n");
    TLinkedBTreeLevelTraverse(tree, TLinkedBTreeVisit);

    printf("\n\n长度为：%d\n", TLinkedBTreeLength(tree));
    printf("深度为：%d\n", TLinkedBTreeDepth(tree));
    printf("带权路径长度为：%d\n", TLinkedBTreeWPL(tree));

    printf("\n\'5\'是否在该表中： ");
    TLinkedBTreeNode* p = NULL;
    TLinkedBTreeContain(tree, 5, &p) == TRUE ? printf("是") : printf("否");
    printf("\n\n从\'5\'到根\'1\'的路径为：\n");
    TLinkedBTreePath(tree, 5);

    TLinkedBTreeDestroy(tree);
    tree = NULL;
}

void ThreadBTreeDemo(){
    printf("二叉树图如下：\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    ThreadBTree tree = NULL;
    //ThreadBTreeCreate(&tree);
    ThreadBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    ThreadBTree head = NULL;
    ThreadBTreeInThreading(&head, tree);

    printf("\n线索化后中序遍历：\n");
    ThreadBTreeInTraverse(head, ThreadBTreeVisit);
}

void HuffManBTreeDemo(){
    char chs[] = {'a', 'b', 'c', 'd'};
    int wts[] = {7, 5, 2, 4};
    int n = sizeof(chs) / sizeof(*chs);

    HTNode hn[HTMAX * 2];//大小为结点数量 + 1
    HTCode hc[HTMAX * 2];//大小为结点数量 + 1

    //HTInitCode(hc, &n);
    HTInitCodeByNums(hc, chs, wts, n);

    HTCreate(hn, hc, n);
    for(int i = 1; i <= n; i++)
        printf("%c ---- %s\n", hc[i].data, hc[i].code);
}

void ParentTreeDemo(){
    int nums[][2] = {
        {1, -1}, {2, 0}, {3, 0}, {4, 0}, {5, 2}, {6, 4}
    };
    printf("树如下图：\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");
    printf("        6\n");

    PTree* tree = NULL;
    //ParentTreeCreate(&tree);
    ParentTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n树的深度为：%d\n", ParentTreeDepth(tree));
    printf("结点\'5\'的深度为：%d\n", ParentTreeNodeDepth(tree, 5));

    printf("\n先序遍历树：\n");
    ParentTreePreTraverse(tree, ParentTreeVisit);
    printf("\n后序遍历树：\n");
    ParentTreePostTraverse(tree, ParentTreeVisit);
    printf("\n层次遍历树：\n");
    ParentTreeLevelTraverse(tree, ParentTreeVisit);

    printf("\n根结点到结点\'6\'的路径为：\n");
    ParentTreePath(tree, 6);
}

void ChildTreeDemo(){
    int nums[][2] = {
        {1, -1}, {2, 0}, {3, 0}, {4, 0}, {5, 2}, {6, 4}, {7, 4}
    };
    printf("树如下图：\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");
    printf("       6 7\n");

    CTree* tree = NULL;
    //ChildTreeCreate(&tree);
    ChildTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n树的深度为：%d\n", ChildTreeDepth(tree));
    printf("结点\'7\'的深度为：%d\n", ChildTreeNodeDepth(tree, 7));

    printf("\n先序遍历树：\n");
    ChildTreePreTraverse(tree, ChildTreeVisit);
    printf("\n后序遍历树：\n");
    ChildTreePostTraverse(tree, ChildTreeVisit);
    printf("\n层次遍历树：\n");
    ChildTreeLevelTraverse(tree, ChildTreeVisit);

    printf("\n根结点到结点\'6\'的路径为：\n");
    ChildTreePath(tree, 6);
}

void CSTreeDemo(){
    int nums[] = {1, 2, 0, 0, 3, 0, 0, 0, 0, 5, 4};//采用完全二叉树法
    printf("树如下图：\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");

    CSTree* tree = NULL;
    //CSTreeCreate(&tree);
    CSTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n树的深度为：%d\n", CSTreeDepth(tree));
    printf("树的长度为：%d\n", CSTreeLength(tree));

    printf("\n先序遍历树：\n");
    CSTreePreTraverse(tree, CSTreeVisit);
    printf("\n后序遍历树：\n");
    CSTreePostTraverse(tree, CSTreeVisit);
    printf("\n层次遍历树：\n");
    CSTreeLevelTraverse(tree, CSTreeVisit);

    printf("\n根结点到结点\'5\'的路径为：\n");
    CSTreePath(tree, 5);
}

void AdjMatrixGraphDemo(){
    printf("示意图：\n");
    printf(" 0    →    4\n");
    printf("↓  ↖     ↑ \n");
    printf(" 1 → 2 → 3\n");

    AdjMatrixGraph* A = NULL, *B = NULL;
    //AdjMatrixGraphCreate(&A);
    AdjMatrixGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("深度搜索：\n");
    AdjMatrixGraphDFS(A);
    printf("\n\n复制图之后广度搜索：\n");
    AdjMatrixGraphCopy(&B, A);
    AdjMatrixGraphHFS(B);

    printf("\n\n");
    AdjMatrixGraphDijkstraPrint(A, 0);

    printf("\n\n");
    AdjMatrixGraphFloydPrint(A);

    //伪无向图
    int m = INT_MAX;
    int graphNums[] = {0, 1, 2, 3, 4};
    EdgeType AdjMatrix[][5] = {
        {0, 9, 2, m, 6},
        {9, 0, 3, m, m},
        {2, 3, 0, 5, m},
        {m, m, 5, 0, 1},
        {6, m, m, 1, 0},
    };
    printf("\n\n示意图：\n");
    printf(" 0 ------- 4\n");
    printf(" |  \\      | \n");
    printf(" 1 -- 2 -- 3\n");
    AdjMatrixGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("\n无向图的最小生成树：普里姆算法\n");
    AdjMatrixGraphPrimPrint(A);
    printf("\n无向图的最小生成树：克鲁斯卡尔算法\n");
    AdjMatrixGraphKruskalPrint(A);

    AdjMatrixGraphDestroy(A);
    AdjMatrixGraphDestroy(B);
}

void AdjListGraphDemo(){
    printf("示意图：\n");
    printf(" 0    →    4\n");
    printf("↓  ↖     ↑ \n");
    printf(" 1 → 2 → 3\n");

    AdjListGraph* A = NULL, *B = NULL;
    //AdjListGraphCreate(&A);
    AdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("深度搜索：\n");
    AdjListGraphDFS(A);
    printf("\n\n复制图之后广度搜索：\n");
    AdjListGraphCopy(&B, A);
    AdjListGraphHFS(B);

    //拓扑排序用
    int m = INT_MAX;
    int graphNums[] = {0, 1, 2, 3, 4};
    EdgeType AdjMatrix[][5] = {
        {0, 9, 2, m, m},
        {m, 0, m, 4, m},
        {m, m, 0, m, 6},
        {m, m, m, 0, 1},
        {m, m, m, m, 0},
    };
    printf("\n\n拓扑排序用示意图：\n");
    printf("  0 → 1 → 3\n");
    printf(" ↓        ↓ \n");
    printf("  2    →  4\n");

    AdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 5);
    printf("\n拓扑排序:\n");
    AdjListGraphTopologicalSort(A);
    printf("\n关键路径:\n");
    AdjListGraphCriticalPath(A);

    AdjListGraphDestroy(A);
    AdjListGraphDestroy(B);
}

void InverseAdjListGraphDemo(){
    printf("示意图：\n");
    printf(" 0    →    4\n");
    printf("↓  ↖     ↑ \n");
    printf(" 1 → 2 → 3\n");

    InverseAdjListGraph* A = NULL, *B = NULL;
    //InverseAdjListGraphCreate(&A);
    InverseAdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("深度搜索：\n");
    InverseAdjListGraphDFS(A);
    printf("\n\n复制图之后广度搜索：\n");
    InverseAdjListGraphCopy(&B, A);
    InverseAdjListGraphHFS(B);

    InverseAdjListGraphDestroy(A);
    InverseAdjListGraphDestroy(B);
}

void OLGraphDemo(){
    printf("示意图：\n");
    printf(" 0    →    4\n");
    printf("↓  ↖     ↑ \n");
    printf(" 1 → 2 → 3\n");

    OLGraph* A = NULL, *B = NULL;
    //OLGraphCreate(&A);
    OLGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("深度搜索：\n");
    OLGraphDFS(A);
    printf("\n\n复制图之后广度搜索：\n");
    OLGraphCopy(&B, A);
    OLGraphHFS(B);

    OLGraphDestroy(A);
    OLGraphDestroy(B);
}

void AdjMultilistGraphDemo(){
    int m = INT_MAX;
    int graphNums[] = {0, 1, 2, 3, 4};
    EdgeType AdjMatrix[][5] = {
        {0, 9, 2, m, 6},
        {9, 0, 3, m, m},
        {2, 3, 0, 5, m},
        {m, m, 5, 0, 1},
        {6, m, m, 1, 0},
    };
    printf("示意图：\n");
    printf(" 0 ------- 4\n");
    printf(" |  \\      | \n");
    printf(" 1 -- 2 -- 3\n");

    AdjMultilistGraph* A = NULL, *B = NULL;
    //AdjMultilistGraphCreate(&A);
    AdjMultilistGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("深度搜索：\n");
    AdjMultilistGraphDFS(A);
    printf("\n\n复制图之后广度搜索：\n");
    AdjMultilistGraphCopy(&B, A);
    AdjMultilistGraphHFS(B);

    AdjMultilistGraphDestroy(A);
    AdjMultilistGraphDestroy(B);
}

void SearchDemo(){
    ElemType nums[] = {0, 3, 7, 1, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("原数据：\n");
    SearchPrint(nums, size);
    //printf("\n顺序查找元素\'1\'的下标：%d\n", SearchSeq(nums, size, 1));

    //SortQuike(nums, size, SortAscendOrder);
    //printf("\n原数据：\n");
    //SearchPrint(nums, size);
    //printf("\n折半查找元素\'7\'的下标：%d\n", SearchSeq(nums, size, 7));

    //SortQuike(nums, size, SortAscendOrder);
    //printf("\n次优查找树查找\'8\'的元素内容为：%d\n", SearchSecondOptimalTree(nums, size, 8));

    LinkedBTree binTree = NULL;
    BinTreeCreate(&binTree);
    for(int i = 0; i < size; i++)//尝试创建并添加
        BinTreeInsert(&binTree, nums[i]);
    //for(int i = 0; i < 3; i++)//尝试删除
    //    BinTreeDelete(&binTree, nums[i]);
    LinkedBTree p;
    BinTreeFind(binTree, 8, NULL, &p);
    printf("\n二叉排序树查找\'8\'的元素内容为：%d\n", p->data);
    printf("\n二叉排序树的平均查找长度为：%.1f\n", BinTreeASL(binTree));


    //AVLTree t = NULL;
    //Status s;
    //for(int i = 0; i < size; i++)//尝试创建并添加
    //    AVLTreeInsert(&t, nums[i], &s);
    //AVLTree p;
    //AVLTreeFind(t, 7, &p);
    //printf("\n二叉平衡树查找\'7\'的元素内容为：%d\n", p->data);
}

void HashTableDemo(){
    ElemType nums[] = {0, 3, 7, 1, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("原数据：\n");
    SearchPrint(nums, size);
    printf("\n");

    HashTable t;
    HashTableInit(&t);
    for(int i = 0; i < size; i++){
        int flag = HashTableInsert(&t, nums[i]);
        if(flag == ERROR)
            printf("\'%d\'插入失败\n", nums[i]);
    }

    for(int i = 0; i < size; i++){
        int addr = 0;
        int flag = HashTableFind(t, nums[i], &addr);
        if(flag == ERROR)
            printf("\'%d\'查找失败\n", nums[i]);
        printf("哈希表中\'%d\'的地址(下标)为：%d\n", nums[i], addr);
    }
}

void SortDemo(){
    ElemType nums[] = {3, 7, 1, 2, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("原数据：\n");
    SortPrint(nums, size);
    //printf("\n直接插入：\n");
    //SortDirectInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n折中插入：\n");
    //SortBinaryInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n冒泡排序：\n");
    //SortBubb(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n快速排序：\n");
    //SortQuike(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n选择排序：\n");
    //SortSelection(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n堆排序：\n");
    //SortHeap(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n归并排序：\n");
    //SortMerge1(nums, size, SortAscendOrder);//非递归
    //SortMerge2(nums, size, SortAscendOrder);//递归
    //SortPrint(nums, size);
    //printf("\n希尔排序：\n");
    //SortShell(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n表排序：\n");
    //ElemType* pos = SortTable(nums, size, SortAscendOrder);
    //for(int i = 0; i < size; i++)
    //    printf("%d ", nums[pos[i]]);
    //printf("\n");
    //free(pos);
    //printf("\n表插入排序：\n");
    //SortTableInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n计数排序：\n");
    //SortCount(nums, size);
    //SortPrint(nums, size);
    printf("\n基数排序：\n");
    SortRadix(nums, size);
    SortPrint(nums, size);
}






















