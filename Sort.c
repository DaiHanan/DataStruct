#include "Sort.h"

//直接插入排序
Status SortDirectInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;
    //未排序中的第一个元素在已排序里找位置插入，未匹配就往前移动，匹配了就插入
    for(int i = 1; i < size; i++){
        int temp = nums[i];//获得该元素
        int j = i - 1;
        while(j >= 0 && order(nums[j], temp)){//未匹配往前移动
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = temp;
    }

    return OK;
}
//折半插入排序
Status SortBinaryInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;
    //和直接插入相似，也是找合适的位置插入
    //但是折半插入会先从已排序数组中间查找，未匹配再折半，匹配后再插入
    for(int i = 1; i < size; i++){
        int temp = nums[i];
        int left = 0, right = i - 1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(order(nums[mid], temp))
                right = mid - 1;
            else
                left = mid + 1;
        }
        for(int j = i - 1; j >= left; j--){
            nums[j + 1] = nums[j];
        }
        nums[left] = temp;
    }

    return OK;
}
//冒泡排序
Status SortBubb(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;
    //利用内循环把每次循环时的最不匹配（最大）元素移到数组尾部
    //利用外循环调整尾部位置
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
            if(order(nums[j], nums[j + 1]))
                _Swap(nums, j, j + 1);
        }
    }

    return OK;
}

//快速排序
Status SortQuike(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;
    //每次以一个基准移动元素，此时基准右边为匹配元素，之后再递归
    _SortQuike1(nums, 0, size - 1, order);

    return OK;
}
//快速排序子函数1,简化主函数
void _SortQuike1(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b)){
    if(left >= right)
        return;
    //划分数组，pivot为基准下标
    int pivot = _SortQuike2(nums, left, right, order);
    //递归
    _SortQuike1(nums, left, pivot - 1, order);
    _SortQuike1(nums, pivot + 1, right, order);
}

//快速排序子函数2,划分函数
int _SortQuike2(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b)){
    int pivot = nums[right];//每次以最右边的元素为基准
    int temp = left;
    for(int i = left; i < right; i++)
        if(order(nums[right], nums[i]))//把匹配错误（小的）的放在左边
            _Swap(nums, temp++, i);
    _Swap(nums, temp, right);//移动基准，此时基准左边匹配失败基准，右边匹配成功基准

    return temp;
}

//选择排序
Status SortSelection(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;
    //每次在未匹配的数组中找最匹配的元素放入已匹配的数组尾部
    for(int i = 0; i < size - 1; i++){
        int temp = i;//先获得第一个未匹配元素下标
        for(int j = i + 1; j < size; j++)
            if(order(nums[temp], nums[j]))//找出未在序列中的最匹配的元素（最小）
                temp = j;
        if(temp != i)//说明找到了另一个（更小）的元素
            _Swap(nums, temp, i);
    }

    return OK;
}

//堆排序
Status SortHeap(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
     if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //先建立最大堆，使使得每个结点比左右结点更不匹配
    for(int i = size / 2 - 1; i >= 0; i--){//从下到上调整
        _SortHeap(nums, i, size, order);
    }
    //每次把‘根’结点（最不匹配）的元素和数组末尾交换，再调整堆
    while(size > 1){
        _Swap(nums, 0, --size);//此时头为最大元素,头尾交换
        _SortHeap(nums, 0, size, order);
    }

    return OK;
}
//堆排序子函数 从下标idx向下进行堆调整
void _SortHeap(ElemType nums[], int idx, int size, int (*order)(ElemType a, ElemType b)){
    int max = idx;
    //左右结点的下标（完全二叉树）
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;
    //在三个点中找最不匹配（最大）点
    if(left < size && order(nums[left], nums[max]))
        max = left;
    if(right < size && order(nums[right], nums[max]))
        max = right;

    if(max != idx){//需要调整
        _Swap(nums, max, idx);
        _SortHeap(nums, max, size, order);
    }
}


//归并排序 非递归
Status SortMerge1(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //把数组分为较小的数组进行排序，从数组大小为1开始
    int left, right, mid;
    for(int i = 1; i < size; i *= 2){
        left = 0;
        while(left + i < size){
            mid = left + i - 1;
            right = mid + i < size ? mid + i : size - 1;
            _SortMerge(nums, left, mid, right, order);
            left = right + 1;
        }

    }

    return OK;
}
//归并排序 递归
Status SortMerge2(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    _SortMerge2(nums, 0, size - 1, order);

    return OK;
}
//归并排序 递归子函数
void _SortMerge2(ElemType nums[], int left, int right, int (*order)(ElemType a, ElemType b)){
    if(left >= right)
        return;
    int mid = (left + right) / 2;
    _SortMerge2(nums, left, mid, order);
    _SortMerge2(nums, mid + 1, right, order);
    _SortMerge(nums, left, mid, right, order);
}
//归并排序 子函数 合并两个已排好序的子数组
Status _SortMerge(ElemType nums[], int left, int mid, int right, int (*order)(ElemType a, ElemType b)){
    //左右数组开始下标
    int l = left;
    int r = mid + 1;
    //申请辅助空间
    int len = right - left + 1;
    ElemType* temp = (ElemType*)malloc(sizeof(ElemType) * len);
    //开始合并
    int idx = 0;
    while(l <= mid && r <= right)
        temp[idx++] = order(nums[l], nums[r]) ? nums[r++] : nums[l++];
    while(l <= mid)
        temp[idx++] = nums[l++];
    while(r <= right)
        temp[idx++] = nums[r++];
    for(int j = 0; j < len; j++)
        nums[left + j] = temp[j];

    free(temp);
}

//希尔排序
Status SortShell(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //和直接插入法相似，只是该排序利用了分组
    //先生成初始增量
    int h = 1;
    while(h * 2 < size)
        h *= 2;
    //分组排序
    while(h > 0){
        for(int i = h; i < size; i++){
            ElemType temp = nums[i];//保存需排序元素
            int j =  i - h;
            while(j >= 0 && order(nums[j], temp)){//不匹配往前找
                nums[j + h] = nums[j];
                j -= h;
            }
            nums[j + h] = temp;//匹配插入
        }

        h /= 2; //扩大分组
    }

    return OK;
}

//表排序
ElemType* SortTable(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return NULL;

    //当元素体积较大，不方便直接交换元素，利用pos数组存储元素位置，交换pos达到排序效果
    //初始化pos数组
    ElemType* pos = (ElemType*)malloc(sizeof(ElemType) * size);
    for(int i = 0; i < size; i++)
        pos[i] = i;
    //简单插入排序
    for(int i = 1; i < size; i++){
        ElemType temp = nums[i];
        int j = i - 1;
        while(j >= 0 && order(nums[pos[j]], temp))//注意比较的是pos[j]下标的元素，原数组未改变
            pos[j + 1] = pos[j--];
        pos[j + 1] = i;
    }

    return pos;
}

//表插入排序
Status SortTableInsertion(ElemType nums[], int size, int (*order)(ElemType a, ElemType b)){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //创建临时数据结构
    typedef struct{
        ElemType data;  //存储数据
        int next;       //下一个结点的下标
    }Node;
    typedef struct{
        Node r[MAXSIZE + 1];//结点数组，0号位表头节点
        //int len;        //链表长度
    }List;
    //建立链表
    List list;
    list.r[0].data = INT_MAX;
    list.r[0].next = 0;//循环链表，空链表
    for(int i = 0; i < size; i++){//循环插入元素
        list.r[i + 1].data = nums[i];
        //修改next
        int q = 0;
        int p = list.r[0].next;
        while(order(list.r[i + 1].data, list.r[p].data)){
            q = p;
            p = list.r[p].next;
        }
        list.r[i + 1].next = p;
        list.r[q].next = i + 1;
    }
    //list.len = size;//修改长度

    //排序完成后赋给原数组
    int p = list.r[0].next;
    for(int i = 0; i < size; i++){
        nums[i] = list.r[p].data;
        p = list.r[p].next;
    }

    return OK;
}


//计数排序
Status SortCount(int nums[], int size){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //计数排序只适合int类型
    //将每个元素作为下标来累加个数，之后再累加个数变成位置数组，再按照位置排序
    //初始化计数数组
    int count[MAXSIZE] = {0};
    //更新计数数组
    for(int i = 0; i < size; i++){
        count[nums[i]]++;
    }
    //使计数数组变成位置（上限）数组
    for(int i = 1; i < MAXSIZE; i++){
        count[i] += count[i - 1];
    }
    //利用临时数组保存排序数组
    int temp[MAXSIZE];
    //反向保存保证了稳定性
    for(int i = size - 1; i >= 0; i--){
        temp[--count[nums[i]]] = nums[i];
    }
    //更新原数组
    for(int i = 0; i < size; i++){
        nums[i] = temp[i];
    }

    return OK;
}

//基数排序
Status SortRadix(int nums[], int size){
    if(!nums || size < 1 || size > MAXSIZE)
        return ERROR;

    //和计数排序相似，只是该排序是按位计数排序
    for(int i = 1; i <= 3; i++)
        _SortRadix1(nums, size, i);

    return OK;
}
//基数排序 子函数 按照第d位进行计数排序
void _SortRadix1(int nums[], int size, int d){
    //设置基数为10，所以计数数组大小为10
    //初始化计数数组
    int count[10] = {0};
    //更新计数数组
    for(int i = 0; i < size; i++){
        int num = _SortRadix2(nums[i], d);
        count[num]++;
    }
    //变为位置数组
    for(int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }
    //建立临时数组并放入元素，反向保证稳定性
    int temp[MAXSIZE];
    for(int i = size - 1; i >= 0; i--){
        int num = _SortRadix2(nums[i], d);
        temp[--count[num]] = nums[i];
    }
    //更新原数组
    for(int i = 0; i < size; i++){
        nums[i] = temp[i];
    }

}
//基数排序 子函数 获取传入元素第d位的数
int _SortRadix2(int num, int d){
    //设元素最多三位
    int a[4] = {1, 1, 10, 100};//弃用0号位
    return (num / a[d]) % 10;
}


//升序 返回1说明前者更大，否则返回0
int SortAscendOrder(ElemType a, ElemType b){
    return a > b ? 1 : 0;
}
//打印
void SortPrint(ElemType nums[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");
}
//交换
void _Swap(ElemType nums[], int i, int j){
    ElemType temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
