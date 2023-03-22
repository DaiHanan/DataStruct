#include "Test.h"
//���Ա�����
ElemType nums[10] = {1, 4, 3, 6, 8, 2, 9, 5, 0, 10};
//����������ȫ����������
int treeNums[] = {1, 2, 3, 4, 5, 6};
//ͼ���ڽӾ�������ͼ������
int graphNums[] = {0, 1, 2, 3, 4};
EdgeType AdjMatrix[][5] = {
    {0, 9, INT_MAX, INT_MAX, 20},
    {INT_MAX, 0, 3, INT_MAX, INT_MAX},
    {2, INT_MAX, 0, 5, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 0, 1},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0},
};

void test(){
    //���Ա�
    //SeqListDemo();
    //LinkedListDemo();
    //DoublyLinkedListDemo();
    //LoopLinkedListDemo();
    //ջ
    //SeqStackDemo();
    //LinkedStackDemo();
    //����
    //SeqQueueDemo();
    //LinkedQueueDemo();
    //��
    //StaticStrDemo();
    //DynamicStrDemo();
    //LinkedStrDemo();
    //����
    //ArrayDemo();
    //TSMatrixDemo();
    //RLSMatrixDemo();
    //OLSMatrixDemo();
    //�����
    //SubGListDemo();
    //LinkedGListDemo();
    //������
    //SeqBTreeDemo();
    //LinkedBTreeDemo();
    //TLinkedBTreeDemo();
    //ThreadBTreeDemo();
    //HuffManBTreeDemo();
    //��
    //ParentTreeDemo();
    //ChildTreeDemo();
    //CSTreeDemo();
    //ͼ
    AdjMatrixGraphDemo();
    //AdjListGraphDemo();
    //InverseAdjListGraphDemo();
    //OLGraphDemo();
    //AdjMultilistGraphDemo();
    //����
    //SearchDemo();
    //HashTableDemo();
    //����
    //SortDemo();
}

//˳���
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
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, SeqListLocateElem(list, elem));

    printf("\nɾ��Ԫ�أ�");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        SeqListDelete(list, rand() % SeqListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\nʣ��Ԫ�أ�\n");
    SeqListOutput(list);
    SeqListDestroy(list);
    list = NULL;
}
//��ʽ��
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
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, LinkedListLocateElem(list, elem));

    printf("\nɾ��Ԫ�أ�");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        LinkedListDelete(list, rand() % LinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\nʣ��Ԫ�أ�\n");
    LinkedListTraverse(list, LinkedListVisit);
    LinkedListDestroy(list);
    list = NULL;
}
//˫������
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
    printf("���Ԫ�� %d ��ǰ����������Ԫ��Ϊ %d\n", node1->data, node2->data);

    ElemType elem;
    DoublyLinkedListGetElem(list, 7, &elem);
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, DoublyLinkedListLocateElem(list, elem));

    printf("\nɾ��Ԫ�أ�");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        DoublyLinkedListDelete(list, rand() % DoublyLinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\nʣ��Ԫ�أ�\n");
    DoublyLinkedListTraverse(list, DoublyLinkedListVisit);
    DoublyLinkedListDestroy(list);
    list = NULL;
}
//ѭ������
void LoopLinkedListDemo(){
    LoopLinkedList* list = NULL;
    LoopLinkedListInit(&list);
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);
    for(int i = 0; i < 10; i++){
        LoopLinkedListInsert(list, i + 1, nums[i]);
    }
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);

    printf("\n�ӵ�%d��Ԫ�ؿ�ʼ������\n", 3);
    LoopLinkedListTraverse(list, 3, LoopLinkedListVisit);

    ElemType elem;
    LoopLinkedListGetElem(list, 7, &elem);
    printf("\nԪ��%d��λ���ǣ�%d\n", elem, LoopLinkedListLocateElem(list, elem));

    printf("\nɾ��Ԫ�أ�");
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        LoopLinkedListDelete(list, rand() % LoopLinkedListLength(list), &elem);
        printf("%d ", elem);
    }
    printf("\nʣ��Ԫ�أ�\n");
    LoopLinkedListTraverse(list, 1, LoopLinkedListVisit);
    LoopLinkedListDestroy(list);
    list = NULL;
}
//˳��ջ
void SeqStackDemo(){
    SeqStack* stack = NULL;
    SeqStackInit(&stack);
    SeqStackTraverse(stack, SeqStackVisit);
    for(int i = 0; i < 10; i++){
        SeqStackPush(stack, nums[i]);
    }
    SeqStackTraverse(stack, SeqStackVisit);

    ElemType elem = 4;
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, SeqStackLocateElem(stack, elem));

    printf("\nɾ��Ԫ�أ�");
    for(int i = 0; i < 4; i++){
        SeqStackPop(stack, &elem);
        printf("%d ", elem);
    }
    SeqStackTop(stack, &elem);
    printf("\n��ʱջ��Ԫ�أ�%d\n", elem);
    printf("ʣ��Ԫ�أ�\n");
    SeqStackTraverse(stack, SeqStackVisit);
    SeqStackDestroy(stack);
    stack = NULL;
}
//��ʽջ
void LinkedStackDemo(){
    LinkedStack* stack = NULL;
    LinkedStackInit(&stack);
    LinkedStackTraverse(stack, LinkedStackVisit);
    for(int i = 0; i < 10; i++){
        LinkedStackPush(stack, nums[i]);
    }
    LinkedStackTraverse(stack, LinkedStackVisit);

    ElemType elem = 4;
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, LinkedStackLocateElem(stack, elem));

    printf("\nɾ��Ԫ�أ�");
    for(int i = 0; i < 4; i++){
        LinkedStackPop(stack, &elem);
        printf("%d ", elem);
    }
    LinkedStackTop(stack, &elem);
    printf("\n��ʱջ��Ԫ�أ�%d\n", elem);
    printf("ʣ��Ԫ�أ�\n");
    LinkedStackTraverse(stack, LinkedStackVisit);
    LinkedStackDestroy(stack);
    stack = NULL;
}
//˳�����
void SeqQueueDemo(){
    SeqQueue* queue = NULL;
    SeqQueueInit(&queue);
    SeqQueueTraverse(queue, SeqQueueVisit);
    for(int i = 0; i < 10; i++){
        SeqQueuePush(queue, nums[i]);
    }
    SeqQueueTraverse(queue, SeqQueueVisit);

    ElemType elem = 5;
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, SeqQueueLocateElem(queue, elem));

    printf("\nɾ��Ԫ�أ�");
    for(int i = 0; i < 4; i++){
        SeqQueuePop(queue, &elem);
        printf("%d ", elem);
    }
    SeqQueueTop(queue, &elem);
    printf("\n��ʱջ��Ԫ�أ�%d\n", elem);
    printf("ʣ��Ԫ�أ�\n");
    SeqQueueTraverse(queue, SeqQueueVisit);
    SeqQueueDestroy(queue);
    queue = NULL;
}
//��ʽ����
void LinkedQueueDemo(){
    LinkedQueue* queue = NULL;
    LinkedQueueInit(&queue);
    LinkedQueueTraverse(queue, LinkedQueueVisit);
    for(int i = 0; i < 10; i++){
        LinkedQueuePush(queue, nums[i]);
    }
    LinkedQueueTraverse(queue, LinkedQueueVisit);

    ElemType elem = 8;
    printf("Ԫ��%d��λ���ǣ�%d\n", elem, LinkedQueueLocateElem(queue, elem));

    printf("\nɾ��Ԫ�أ�");
    for(int i = 0; i < 4; i++){
        LinkedQueuePop(queue, &elem);
        printf("%d ", elem);
    }
    LinkedQueueTop(queue, &elem);
    printf("\n��ʱջ��Ԫ�أ�%d\n", elem);
    printf("ʣ��Ԫ�أ�\n");
    LinkedQueueTraverse(queue, LinkedQueueVisit);
    LinkedQueueDestroy(queue);
    queue = NULL;
}
//��̬��
void StaticStrDemo(){
    StaticStr* str1 = NULL;
    StaticStrInit(&str1);
    StaticStrPrint(str1);
    StaticStrAssign(str1, "122");
    StaticStrPrint(str1);
    printf("����Ϊ��%d\n", StaticStrLength(str1));

    StaticStr* str2 = NULL;
    StaticStrInit(&str2);
    StaticStrAssign(str2, "452");

    StaticStrCopy(str1, str2);
    printf("\n������\n");
    StaticStrPrint(str1);

    StaticStr* str3 = NULL;
    StaticStrInit(&str3);
    StaticStrAssign(str3, "782");
    printf("\n���Ӻ�\n");
    StaticStrConcat(str1, str2, str3);
    StaticStrPrint(str1);

    printf("\nstr1 : ");
    StaticStrPrint(str1);
    printf("str3 : ");
    StaticStrPrint(str3);
    printf("str1 ");
    if(StaticStrCompare(str1, str3) < 0)
        printf("С��");
    else
        printf("���ڵ���");
    printf(" str3\n");

    StaticStrInsert(str1, str3, 2);
    printf("\nstr3����str1�ĵ�2��λ�ú�str1 Ϊ��\n");
    StaticStrPrint(str1);

    StaticStrDelete(str1, 2, 2);
    printf("\nɾ��str1�е� 2 ��λ�ÿ�ʼ��Ϊ 2 ���Ӵ���str1 Ϊ��\n");
    StaticStrPrint(str1);

    StaticStrSubStr(str2, str1, 2, 4);
    printf("\nstr1�д�λ�� 2 ��ʼ����Ϊ 4 ���Ӵ�Ϊ��\n");
    StaticStrPrint(str2);

    printf("\nstr1 Ϊ��\n");
    StaticStrPrint(str1);
    StaticStrAssign(str2, "2");
    StaticStrAssign(str3, "AAA");
    StaticStrReplace(str1, str2, str3);
    printf("��\' AAA \'�滻str1�����е�\'2\'��\nstr1 Ϊ��\n");
    StaticStrPrint(str1);
    StaticStrDestroy(str1);
    StaticStrDestroy(str2);
    StaticStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//��̬��
void DynamicStrDemo(){
    DynamicStr* str1 = NULL;
    DynamicStrInit(&str1);
    DynamicStrPrint(str1);
    DynamicStrAssign(str1, "112");
    DynamicStrPrint(str1);
    printf("����Ϊ��%d\n", DynamicStrLength(str1));

    DynamicStr* str2 = NULL;
    DynamicStrInit(&str2);
    DynamicStrAssign(str2, "156");

    DynamicStrCopy(str1, str2);
    printf("\n������\n");
    DynamicStrPrint(str1);

    DynamicStr* str3 = NULL;
    DynamicStrInit(&str3);
    DynamicStrAssign(str3, "189");
    printf("\n���Ӻ�\n");
    DynamicStrConcat(str1, str2, str3);
    DynamicStrPrint(str1);

    printf("\nstr1 : ");
    DynamicStrPrint(str1);
    printf("str3 : ");
    DynamicStrPrint(str3);
    printf("str1 ");
    if(DynamicStrCompare(str1, str3) < 0)
        printf("С��");
    else
        printf("���ڵ���");
    printf(" str3\n");

    DynamicStrInsert(str1, str3, 2);
    printf("\nstr3����str1�ĵ�2��λ�ú�str1 Ϊ��\n");
    DynamicStrPrint(str1);

    DynamicStrDelete(str1, 2, 2);
    printf("\nɾ��str1�е� 2 ��λ�ÿ�ʼ��Ϊ 2 ���Ӵ���str1 Ϊ��\n");
    DynamicStrPrint(str1);

    DynamicStrSubStr(str2, str1, 2, 4);
    printf("\nstr1�д�λ�� 2 ��ʼ����Ϊ 4 ���Ӵ�Ϊ��\n");
    DynamicStrPrint(str2);

    printf("\nstr1 Ϊ��\n");
    DynamicStrPrint(str1);
    DynamicStrAssign(str2, "1");
    DynamicStrAssign(str3, "AAA");
    DynamicStrReplace(str1, str2, str3);
    printf("��\' AAA \'�滻str1�����е�\'1\'��\nstr1 Ϊ��\n");
    DynamicStrPrint(str1);
    DynamicStrDestroy(str1);
    DynamicStrDestroy(str2);
    DynamicStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//������
void LinkedStrDemo(){
    LinkedStr* str1 = NULL;
    LinkedStrInit(&str1);
    LinkedStrPrint(str1);
    LinkedStrAssign(str1, "123");
    LinkedStrPrint(str1);
    printf("����Ϊ��%d\n", LinkedStrLength(str1));

    LinkedStr* str2 = NULL;
    LinkedStrInit(&str2);
    LinkedStrAssign(str2, "406");

    LinkedStrCopy(str1, str2);
    printf("\n������\n");
    LinkedStrPrint(str1);

    LinkedStr* str3 = NULL;
    LinkedStrInit(&str3);
    LinkedStrAssign(str3, "709");
    printf("\n���Ӻ�\n");
    LinkedStrConcat(str1, str2, str3);
    LinkedStrPrint(str1);

    printf("\nstr1 : ");
    LinkedStrPrint(str1);
    printf("str3 : ");
    LinkedStrPrint(str3);
    printf("str1 ");
    if(LinkedStrCompare(str1, str3) < 0)
        printf("С��");
    else
        printf("���ڵ���");
    printf(" str3\n");

    LinkedStrInsert(str1, str3, 2);
    printf("\nstr3����str1�ĵ�2��λ�ú�str1 Ϊ��\n");
    LinkedStrPrint(str1);

    LinkedStrDelete(str1, 2, 2);
    printf("\nɾ��str1�е� 2 ��λ�ÿ�ʼ��Ϊ 2 ���Ӵ���str1 Ϊ��\n");
    LinkedStrPrint(str1);

    LinkedStrSubStr(str2, str1, 2, 4);
    printf("\nstr1�д�λ�� 2 ��ʼ����Ϊ 4 ���Ӵ�Ϊ��\n");
    LinkedStrPrint(str2);

    printf("\nstr1 Ϊ��\n");
    LinkedStrPrint(str1);
    LinkedStrAssign(str2, "0");
    LinkedStrAssign(str3, "AAA");
    LinkedStrReplace(str1, str2, str3);
    printf("��\' AAA \'�滻str1�����е�\'0\'��\nstr1 Ϊ��\n");
    LinkedStrPrint(str1);

    LinkedStrDestroy(str1);
    LinkedStrDestroy(str2);
    LinkedStrDestroy(str3);
    str1 = str2 = str3 = NULL;
}
//����
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
    printf("����������±�Ϊ1 1 0 ��Ԫ��Ϊ :%-3d\n", temp);
    ArrayDestroy(A);
    ArrayDestroy(B);
    A = B = NULL;
}
//��Ԫ��ϡ�����
void TSMatrixDemo(){
    TSMatrix* A = NULL;
    int ii = 3, jj = 3;
    int temp = 1;
    TSMatrixInit(&A, ii, jj);
    printf("��ʼ������\n");
    TSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            TSMatrixAssign(A, i * 12 + j, i, j);
        }
    }
    TSMatrixPrint(A);

    printf("\nɾ������Ԫ��1,1��\n");
    TSMatrixAssign(A, 0, 1, 1);
    TSMatrixPrint(A);

    printf("\n���ӷ���Ԫ��1,1��\n");
    TSMatrixAssign(A, 99, 1, 1);
    TSMatrixPrint(A);

    printf("\n�ı����Ԫ��1,1��\n");
    TSMatrixAssign(A, 66, 1, 1);
    TSMatrixPrint(A);
    printf("\n");

    TSMatrix* B = NULL;
    TSMatrixInit(&B, 6, 6);
    TSMatrixCopy(B, A);
    TSMatrixValue(A, &temp, 2, 1);
    printf("ԭ��������±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    TSMatrixValue(B, &temp, 2, 1);
    printf("���ƾ�����±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    TSMatrixDestroy(A);
    TSMatrixDestroy(B);
    A = B = NULL;
}
//���߼�����ϡ�����
void RLSMatrixDemo(){
    RLSMatrix* A = NULL;
    int ii = 3, jj = 3;
    int temp = 1;
    RLSMatrixInit(&A, ii, jj);
    printf("��ʼ������\n");
    RLSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            RLSMatrixAssign(A, i * 12 + j, i, j);
        }
    }
    RLSMatrixPrint(A);

    printf("\nɾ������Ԫ��1,0����1,1��\n");
    RLSMatrixAssign(A, 0, 1, 0);
    RLSMatrixAssign(A, 0, 1, 1);
    RLSMatrixPrint(A);

    printf("\n���ӷ���Ԫ��1,1��\n");
    RLSMatrixAssign(A, 99, 1, 1);
    RLSMatrixPrint(A);

    printf("\n�ı����Ԫ��1,1��\n");
    RLSMatrixAssign(A, 66, 1, 1);
    RLSMatrixPrint(A);
    printf("\n");

    int col = 0;
    RLSMatrixGetLineFirstElem(A, 1, &col);
    printf("��2�еĵ�һ������Ԫ�±�Ϊ��%d\n", col);
    printf("\n");

    RLSMatrix* B = NULL;
    RLSMatrixInit(&B, 6, 6);
    RLSMatrixCopy(B, A);
    RLSMatrixValue(A, &temp, 2, 1);
    printf("ԭ��������±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    RLSMatrixValue(B, &temp, 2, 1);
    printf("���ƾ�����±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    RLSMatrixDestroy(A);
    RLSMatrixDestroy(B);
    A = B = NULL;
}
//ʮ������ϡ�����
void OLSMatrixDemo(){
    OLSMatrix* A = NULL;
    int ii = 5, jj = 4;
    int temp = 1;
    OLSMatrixInit(&A, ii, jj);
    printf("��ʼ������\n");
    OLSMatrixPrint(A);
    printf("\n");
    for(int i = 0; i < ii; i++){
        for(int j = 0; j < jj; j++){
            if(OLSMatrixAssign(A, i * 12 + j, i, j) != OK)
                return ERROR;
        }
    }
    OLSMatrixPrint(A);

    printf("\nɾ������Ԫ��2,2��\n");
    OLSMatrixAssign(A, 0, 2, 2);
    OLSMatrixPrint(A);

    printf("\n���ӷ���Ԫ��2,2��\n");
    OLSMatrixAssign(A, 99, 2, 2);
    OLSMatrixPrint(A);

    printf("\n�ı����Ԫ��2,2��\n");
    OLSMatrixAssign(A, 66, 2, 2);
    OLSMatrixPrint(A);
    printf("\n");

    OLSMatrix* B = NULL;
    OLSMatrixInit(&B, 6, 6);
    OLSMatrixCopy(B, A);
    OLSMatrixValue(A, &temp, 2, 1);
    printf("ԭ��������±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    OLSMatrixValue(B, &temp, 2, 1);
    printf("���ƾ�����±�Ϊ2 1 ��Ԫ��Ϊ :%-3d\n", temp);
    OLSMatrixDestroy(A);
    OLSMatrixDestroy(B);
    A = B = NULL;
}
//�ӱ�����
void SubGListDemo(){
    SubGList L = NULL;
    SubGListInit(&L);
    StaticStr* S = NULL;
    StaticStrInit(&S);
    StaticStrAssign(S, "(a,(b),c,(d,(e)))");
    SubGListCreate(&L, S);
    printf("�����ֵ�ַ���Ϊ��\n");
    StaticStrPrint(S);
    printf("\n��ӡԭ��\n");
    SubGListTraverse(&L, SubGListVisit);

    printf("\n\n��ĳ���Ϊ��%d\n", SubGListLength(&L));
    printf("������Ϊ��%d\n", SubGListDepth(&L));

    SubGList T = NULL;
    SubGListInit(&T);
    SubGListCopy(&T, &L);
    printf("\n��ӡ���Ʊ�\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListGetHead(&T, &L);
    printf("\n\n��ӡ��ͷ��\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListGetTail(&T, &L);
    printf("\n��ӡ��β��\n");
    SubGListTraverse(&T, SubGListVisit);

    SubGListDestroy(&T);
    T = NULL;
    StaticStrAssign(S, "(f,(g))");
    SubGListCreate(&T, S);
    printf("\n\n����±�ͷ(f,(g))\n");
    SubGListInsertHead(&L, &T);
    printf("��ӡԭ��\n");
    SubGListTraverse(&L, SubGListVisit);

    printf("\n\nɾ����ͷ\n");
    SubGListDeleteHead(&L, &T);
    printf("��ӡԭ��\n");
    SubGListTraverse(&L, SubGListVisit);
    SubGListDestroy(&L);
    SubGListDestroy(&T);
    L = T = NULL;
}
//��ʽ�����
void LinkedGListDemo(){
	LinkedGList L = NULL;
    LinkedGListInit(&L);
    StaticStr* S = NULL;
    StaticStrInit(&S);

    StaticStrAssign(S, "(a,(b),c,(d,(e)))");
    LinkedGListCreate(&L, S);
    printf("�����ֵ�ַ���Ϊ��\n");
    StaticStrPrint(S);
    printf("\n��ӡԭ��\n");
    LinkedGListTraverse(&L, LinkedGListVisit);


    printf("\n\n��ĳ���Ϊ��%d\n", LinkedGListLength(&L));
    printf("������Ϊ��%d\n", LinkedGListDepth(&L));

    LinkedGList T = NULL;
    LinkedGListInit(&T);//�þ���Բ�Ҫ
    LinkedGListCopy(&T, &L);
    printf("\n��ӡ���Ʊ�\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListGetHead(&T, &L);
    printf("\n\n��ӡ��ͷ��\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListGetTail(&T, &L);
    printf("\n��ӡ��β��\n");
    LinkedGListTraverse(&T, LinkedGListVisit);

    LinkedGListDestroy(&T);
    T = NULL;
    StaticStrAssign(S, "(f,(g))");
    LinkedGListCreate(&T, S);
    printf("\n\n����±�ͷ(f,(g))\n");
    LinkedGListInsertHead(&L, &T);
    printf("��ӡԭ��\n");
    LinkedGListTraverse(&L, LinkedGListVisit);

    printf("\n\nɾ����ͷ\n");
    LinkedGListDeleteHead(&L, &T);
    printf("��ӡԭ��\n");
    LinkedGListTraverse(&L, LinkedGListVisit);

    LinkedGListDestroy(&L);
    LinkedGListDestroy(&T);
    L = T = NULL;
}
//˳�������
void SeqBTreeDemo(){
    printf("������ͼ���£�\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    SeqBTree tree;
    SeqBTreeInit(tree);
    //SeqBTreeCreate(tree);
    SeqBTreeCreateByNums(tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n�������\n");
    SeqBTreePreTraverse(tree, SeqBTreeVisit);
    printf("\n�������\n");
    SeqBTreeInTraverse(tree, SeqBTreeVisit);
    printf("\n�������\n");
    SeqBTreePostTraverse(tree, SeqBTreeVisit);
    printf("\n��α���\n");
    SeqBTreeLevelTraverse(tree, SeqBTreeVisit);

    printf("\n\n����Ϊ��%d\n", SeqBTreeLength(tree));
    printf("���Ϊ��%d\n", SeqBTreeDepth(tree));
    printf("��Ȩ·������Ϊ��%d\n", SeqBTreeWPL(tree));

    printf("\n\'5\'�Ƿ��ڸñ��У� ");
    SeqBTreeContain(tree, 5) == TRUE ? printf("��") : printf("��");
    printf("\n\n�Ӹ�\'1\'��\'5\'��·��Ϊ��\n");
    SeqBTreePath(tree, 5);
}
//������ʽ������
void LinkedBTreeDemo(){
    printf("������ͼ���£�\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    LinkedBTree tree = NULL;
    //LinkedBTreeCreate(&tree);
    LinkedBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n�������\n");
    LinkedBTreePreTraverse(tree, LinkedBTreeVisit);
    printf("\n�������\n");
    LinkedBTreeInTraverse(tree, LinkedBTreeVisit);
    printf("\n�������\n");
    LinkedBTreePostTraverse(tree, LinkedBTreeVisit);
    printf("\n��α���\n");
    LinkedBTreeLevelTraverse(tree, LinkedBTreeVisit);

    printf("\n\n����Ϊ��%d\n", LinkedBTreeLength(tree));
    printf("���Ϊ��%d\n", LinkedBTreeDepth(tree));
    printf("��Ȩ·������Ϊ��%d\n", LinkedBTreeWPL(tree));
	printf("Ҷ�ӽ�����Ϊ��%d\n", LinkedBTreeLeafCount(tree));
	printf("��Ϊ1�Ľ�����Ϊ��%d\n", LinkedBTreeNode_1Count(tree));

    printf("\n\'5\'�Ƿ��ڸñ��У� ");
    LinkedBTreeContain(tree, 5) == TRUE ? printf("��") : printf("��");

    printf("\n\n��\'5\'����\'1\'��·��Ϊ��\n");
    LinkedBTreePath(tree, 5);

	printf("\n\n����Ҷ�ӽ�㵽����·��Ϊ��\n");
    LinkedBTreeAllPath(tree);

	LinkedBTreeNode* p = LinkedBTreeGetNode(tree, 6);
	if(p)
		printf("\n\n��ý��\'6\'����ӡ�ý������ݣ�%d\n", p->data);

    printf("\n�������н������ҽ��֮���������������\n");
    LinkedBTreeReverseNode(tree);
    LinkedBTreePreTraverse(tree, LinkedBTreeVisit);

	printf("\n");
    LinkedBTreeDestroy(tree);
    tree = NULL;
}

//������ʽ������
void TLinkedBTreeDemo(){
    printf("������ͼ���£�\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    TLinkedBTree tree = NULL;
    //TLinkedBTreeCreate(&tree);
    TLinkedBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    printf("\n�������\n");
    TLinkedBTreePreTraverse(tree, TLinkedBTreeVisit);
    printf("\n�������\n");
    TLinkedBTreeInTraverse(tree, TLinkedBTreeVisit);
    printf("\n�������\n");
    TLinkedBTreePostTraverse(tree, TLinkedBTreeVisit);
    printf("\n��α���\n");
    TLinkedBTreeLevelTraverse(tree, TLinkedBTreeVisit);

    printf("\n\n����Ϊ��%d\n", TLinkedBTreeLength(tree));
    printf("���Ϊ��%d\n", TLinkedBTreeDepth(tree));
    printf("��Ȩ·������Ϊ��%d\n", TLinkedBTreeWPL(tree));

    printf("\n\'5\'�Ƿ��ڸñ��У� ");
    TLinkedBTreeNode* p = NULL;
    TLinkedBTreeContain(tree, 5, &p) == TRUE ? printf("��") : printf("��");
    printf("\n\n��\'5\'����\'1\'��·��Ϊ��\n");
    TLinkedBTreePath(tree, 5);

    TLinkedBTreeDestroy(tree);
    tree = NULL;
}

void ThreadBTreeDemo(){
    printf("������ͼ���£�\n");
    printf("\t 1\n");
    printf("    2  \t      3\n");
    printf("  4   5\t   6\n");

    ThreadBTree tree = NULL;
    //ThreadBTreeCreate(&tree);
    ThreadBTreeCreateByNums(&tree, treeNums, sizeof(treeNums) / sizeof(*treeNums));

    ThreadBTree head = NULL;
    ThreadBTreeInThreading(&head, tree);

    printf("\n�����������������\n");
    ThreadBTreeInTraverse(head, ThreadBTreeVisit);
}

void HuffManBTreeDemo(){
    char chs[] = {'a', 'b', 'c', 'd'};
    int wts[] = {7, 5, 2, 4};
    int n = sizeof(chs) / sizeof(*chs);

    HTNode hn[HTMAX * 2];//��СΪ������� + 1
    HTCode hc[HTMAX * 2];//��СΪ������� + 1

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
    printf("������ͼ��\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");
    printf("        6\n");

    PTree* tree = NULL;
    //ParentTreeCreate(&tree);
    ParentTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n�������Ϊ��%d\n", ParentTreeDepth(tree));
    printf("���\'5\'�����Ϊ��%d\n", ParentTreeNodeDepth(tree, 5));

    printf("\n�����������\n");
    ParentTreePreTraverse(tree, ParentTreeVisit);
    printf("\n�����������\n");
    ParentTreePostTraverse(tree, ParentTreeVisit);
    printf("\n��α�������\n");
    ParentTreeLevelTraverse(tree, ParentTreeVisit);

    printf("\n����㵽���\'6\'��·��Ϊ��\n");
    ParentTreePath(tree, 6);
}

void ChildTreeDemo(){
    int nums[][2] = {
        {1, -1}, {2, 0}, {3, 0}, {4, 0}, {5, 2}, {6, 4}, {7, 4}
    };
    printf("������ͼ��\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");
    printf("       6 7\n");

    CTree* tree = NULL;
    //ChildTreeCreate(&tree);
    ChildTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n�������Ϊ��%d\n", ChildTreeDepth(tree));
    printf("���\'7\'�����Ϊ��%d\n", ChildTreeNodeDepth(tree, 7));

    printf("\n�����������\n");
    ChildTreePreTraverse(tree, ChildTreeVisit);
    printf("\n�����������\n");
    ChildTreePostTraverse(tree, ChildTreeVisit);
    printf("\n��α�������\n");
    ChildTreeLevelTraverse(tree, ChildTreeVisit);

    printf("\n����㵽���\'6\'��·��Ϊ��\n");
    ChildTreePath(tree, 6);
}

void CSTreeDemo(){
    int nums[] = {1, 2, 0, 0, 3, 0, 0, 0, 0, 5, 4};//������ȫ��������
    printf("������ͼ��\n");
    printf("        1\n");
    printf("    2   3   4  \n");
    printf("        5\n");

    CSTree* tree = NULL;
    //CSTreeCreate(&tree);
    CSTreeCreateByNums(&tree, nums, sizeof(nums) / sizeof(*nums));

    printf("\n�������Ϊ��%d\n", CSTreeDepth(tree));
    printf("���ĳ���Ϊ��%d\n", CSTreeLength(tree));

    printf("\n�����������\n");
    CSTreePreTraverse(tree, CSTreeVisit);
    printf("\n�����������\n");
    CSTreePostTraverse(tree, CSTreeVisit);
    printf("\n��α�������\n");
    CSTreeLevelTraverse(tree, CSTreeVisit);

    printf("\n����㵽���\'5\'��·��Ϊ��\n");
    CSTreePath(tree, 5);
}

void AdjMatrixGraphDemo(){
    printf("ʾ��ͼ��\n");
    printf(" 0    ��    4\n");
    printf("��  �I     �� \n");
    printf(" 1 �� 2 �� 3\n");

    AdjMatrixGraph* A = NULL, *B = NULL;
    //AdjMatrixGraphCreate(&A);
    AdjMatrixGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("���������\n");
    AdjMatrixGraphDFS(A);
    printf("\n\n����ͼ֮����������\n");
    AdjMatrixGraphCopy(&B, A);
    AdjMatrixGraphHFS(B);

    printf("\n\n");
    AdjMatrixGraphDijkstraPrint(A, 0);

    printf("\n\n");
    AdjMatrixGraphFloydPrint(A);

    //α����ͼ
    int m = INT_MAX;
    int graphNums[] = {0, 1, 2, 3, 4};
    EdgeType AdjMatrix[][5] = {
        {0, 9, 2, m, 6},
        {9, 0, 3, m, m},
        {2, 3, 0, 5, m},
        {m, m, 5, 0, 1},
        {6, m, m, 1, 0},
    };
    printf("\n\nʾ��ͼ��\n");
    printf(" 0 ------- 4\n");
    printf(" |  \\      | \n");
    printf(" 1 -- 2 -- 3\n");
    AdjMatrixGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("\n����ͼ����С������������ķ�㷨\n");
    AdjMatrixGraphPrimPrint(A);
    printf("\n����ͼ����С����������³˹�����㷨\n");
    AdjMatrixGraphKruskalPrint(A);

    AdjMatrixGraphDestroy(A);
    AdjMatrixGraphDestroy(B);
}

void AdjListGraphDemo(){
    printf("ʾ��ͼ��\n");
    printf(" 0    ��    4\n");
    printf("��  �I     �� \n");
    printf(" 1 �� 2 �� 3\n");

    AdjListGraph* A = NULL, *B = NULL;
    //AdjListGraphCreate(&A);
    AdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("���������\n");
    AdjListGraphDFS(A);
    printf("\n\n����ͼ֮����������\n");
    AdjListGraphCopy(&B, A);
    AdjListGraphHFS(B);

    //����������
    int m = INT_MAX;
    int graphNums[] = {0, 1, 2, 3, 4};
    EdgeType AdjMatrix[][5] = {
        {0, 9, 2, m, m},
        {m, 0, m, 4, m},
        {m, m, 0, m, 6},
        {m, m, m, 0, 1},
        {m, m, m, m, 0},
    };
    printf("\n\n����������ʾ��ͼ��\n");
    printf("  0 �� 1 �� 3\n");
    printf(" ��        �� \n");
    printf("  2    ��  4\n");

    AdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 5);
    printf("\n��������:\n");
    AdjListGraphTopologicalSort(A);
    printf("\n�ؼ�·��:\n");
    AdjListGraphCriticalPath(A);

    AdjListGraphDestroy(A);
    AdjListGraphDestroy(B);
}

void InverseAdjListGraphDemo(){
    printf("ʾ��ͼ��\n");
    printf(" 0    ��    4\n");
    printf("��  �I     �� \n");
    printf(" 1 �� 2 �� 3\n");

    InverseAdjListGraph* A = NULL, *B = NULL;
    //InverseAdjListGraphCreate(&A);
    InverseAdjListGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("���������\n");
    InverseAdjListGraphDFS(A);
    printf("\n\n����ͼ֮����������\n");
    InverseAdjListGraphCopy(&B, A);
    InverseAdjListGraphHFS(B);

    InverseAdjListGraphDestroy(A);
    InverseAdjListGraphDestroy(B);
}

void OLGraphDemo(){
    printf("ʾ��ͼ��\n");
    printf(" 0    ��    4\n");
    printf("��  �I     �� \n");
    printf(" 1 �� 2 �� 3\n");

    OLGraph* A = NULL, *B = NULL;
    //OLGraphCreate(&A);
    OLGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("���������\n");
    OLGraphDFS(A);
    printf("\n\n����ͼ֮����������\n");
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
    printf("ʾ��ͼ��\n");
    printf(" 0 ------- 4\n");
    printf(" |  \\      | \n");
    printf(" 1 -- 2 -- 3\n");

    AdjMultilistGraph* A = NULL, *B = NULL;
    //AdjMultilistGraphCreate(&A);
    AdjMultilistGraphCreateByNums(&A, graphNums, AdjMatrix, 5, 6);

    printf("���������\n");
    AdjMultilistGraphDFS(A);
    printf("\n\n����ͼ֮����������\n");
    AdjMultilistGraphCopy(&B, A);
    AdjMultilistGraphHFS(B);

    AdjMultilistGraphDestroy(A);
    AdjMultilistGraphDestroy(B);
}

void SearchDemo(){
    ElemType nums[] = {0, 3, 7, 1, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("ԭ���ݣ�\n");
    SearchPrint(nums, size);
    //printf("\n˳�����Ԫ��\'1\'���±꣺%d\n", SearchSeq(nums, size, 1));

    //SortQuike(nums, size, SortAscendOrder);
    //printf("\nԭ���ݣ�\n");
    //SearchPrint(nums, size);
    //printf("\n�۰����Ԫ��\'7\'���±꣺%d\n", SearchSeq(nums, size, 7));

    //SortQuike(nums, size, SortAscendOrder);
    //printf("\n���Ų���������\'8\'��Ԫ������Ϊ��%d\n", SearchSecondOptimalTree(nums, size, 8));

    LinkedBTree binTree = NULL;
    BinTreeCreate(&binTree);
    for(int i = 0; i < size; i++)//���Դ��������
        BinTreeInsert(&binTree, nums[i]);
    //for(int i = 0; i < 3; i++)//����ɾ��
    //    BinTreeDelete(&binTree, nums[i]);
    LinkedBTree p;
    BinTreeFind(binTree, 8, NULL, &p);
    printf("\n��������������\'8\'��Ԫ������Ϊ��%d\n", p->data);
    printf("\n������������ƽ�����ҳ���Ϊ��%.1f\n", BinTreeASL(binTree));


    //AVLTree t = NULL;
    //Status s;
    //for(int i = 0; i < size; i++)//���Դ��������
    //    AVLTreeInsert(&t, nums[i], &s);
    //AVLTree p;
    //AVLTreeFind(t, 7, &p);
    //printf("\n����ƽ��������\'7\'��Ԫ������Ϊ��%d\n", p->data);
}

void HashTableDemo(){
    ElemType nums[] = {0, 3, 7, 1, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("ԭ���ݣ�\n");
    SearchPrint(nums, size);
    printf("\n");

    HashTable t;
    HashTableInit(&t);
    for(int i = 0; i < size; i++){
        int flag = HashTableInsert(&t, nums[i]);
        if(flag == ERROR)
            printf("\'%d\'����ʧ��\n", nums[i]);
    }

    for(int i = 0; i < size; i++){
        int addr = 0;
        int flag = HashTableFind(t, nums[i], &addr);
        if(flag == ERROR)
            printf("\'%d\'����ʧ��\n", nums[i]);
        printf("��ϣ����\'%d\'�ĵ�ַ(�±�)Ϊ��%d\n", nums[i], addr);
    }
}

void SortDemo(){
    ElemType nums[] = {3, 7, 1, 2, 9, 8, 2};
    int size = sizeof(nums) / sizeof(*nums);
    printf("ԭ���ݣ�\n");
    SortPrint(nums, size);
    //printf("\nֱ�Ӳ��룺\n");
    //SortDirectInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n���в��룺\n");
    //SortBinaryInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\nð������\n");
    //SortBubb(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n��������\n");
    //SortQuike(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\nѡ������\n");
    //SortSelection(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n������\n");
    //SortHeap(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n�鲢����\n");
    //SortMerge1(nums, size, SortAscendOrder);//�ǵݹ�
    //SortMerge2(nums, size, SortAscendOrder);//�ݹ�
    //SortPrint(nums, size);
    //printf("\nϣ������\n");
    //SortShell(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n������\n");
    //ElemType* pos = SortTable(nums, size, SortAscendOrder);
    //for(int i = 0; i < size; i++)
    //    printf("%d ", nums[pos[i]]);
    //printf("\n");
    //free(pos);
    //printf("\n���������\n");
    //SortTableInsertion(nums, size, SortAscendOrder);
    //SortPrint(nums, size);
    //printf("\n��������\n");
    //SortCount(nums, size);
    //SortPrint(nums, size);
    printf("\n��������\n");
    SortRadix(nums, size);
    SortPrint(nums, size);
}






















