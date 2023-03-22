#include "AdjMultilistGraph.h"

//动态创建图
Status AdjMultilistGraphCreate(AdjMultilistGraph** graph){
    if(!graph)
        return ERROR;
    AdjMultilistGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (AdjMultilistGraph*)malloc(sizeof(AdjMultilistGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败

    printf("请输入顶点个数和边数（空格隔开）：\n");
    int size;
    scanf("%d %d", &size, &(*graph)->numEdges);
    (*graph)->numVertexes = size;

    printf("请输入顶点的值（空格隔开）：\n");
    for(int i = 0; i < size; i++){
        scanf("%d", &(*graph)->list[i].data);
        (*graph)->list[i].first = NULL;//初始化边表的头指针
    }
    printf("\n请输入边（vi，vj）的 下标i、j和该边的权值 （空格隔开）：\n");
    int from, to;
    for(int i = 0; i < (*graph)->numEdges; i++){
        scanf("%d %d", &from, &to);//输入下标
        //创建新的边结点
        AdjMultilistEdgeNode* newEdgeNode =
        (AdjMultilistEdgeNode*)malloc(sizeof(AdjMultilistEdgeNode));
        if(!newEdgeNode)
            return OVERFLOW;
        //边结点中的存储下标
        newEdgeNode->ivex = from;
        newEdgeNode->jvex = to;
        //边结点中的权值
        scanf("%d", &newEdgeNode->weight);
        //连接边结点（头插法）
        //i
        newEdgeNode->ilink = (*graph)->list[from].first;
        (*graph)->list[from].first = newEdgeNode;
        //j
        newEdgeNode->jlink = (*graph)->list[to].first;
        (*graph)->list[to].first = newEdgeNode;
    }
    return OK;
}
//利用（邻接）数组创建图，方便测试
Status AdjMultilistGraphCreateByNums(AdjMultilistGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize){
    if(!graph)
        return ERROR;
    AdjMultilistGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (AdjMultilistGraph*)malloc(sizeof(AdjMultilistGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*graph)->numEdges = EdgeSize;
    (*graph)->numVertexes = size;
    //更新顶点结点
    for(int i = 0; i < size; i++){
        (*graph)->list[i].data = vexs[i];
        (*graph)->list[i].first = NULL;//初始化边表的头指针
    }
    //更新边结点，因为对称所以只读上三角矩阵
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            if(*(arc + i * size + j) != INT_MAX){//邻接矩阵中该点有权值时
                //创建新的边结点
                AdjMultilistEdgeNode* newEdgeNode =
                (AdjMultilistEdgeNode*)malloc(sizeof(AdjMultilistEdgeNode));
                if(!newEdgeNode)
                    return OVERFLOW;
                //边结点中的存储下标
                newEdgeNode->ivex = i;
                newEdgeNode->jvex = j;
                //边结点中的权值
                newEdgeNode->weight = *(arc + i * size + j);
                //连接边结点（头插法）
                //出
                newEdgeNode->ilink = (*graph)->list[i].first;
                (*graph)->list[i].first = newEdgeNode;
                //入
                newEdgeNode->jlink = (*graph)->list[j].first;
                (*graph)->list[j].first = newEdgeNode;
                }
            }
    }
    return OK;
}
//销毁图
Status AdjMultilistGraphDestroy(AdjMultilistGraph* graph){
    if(!graph)
        return ERROR;
    AdjMultilistEdgeNode* p, *q;//临时指针
    for(int i = 0; i < graph->numVertexes; i++){
        //按照出弧指针一直释放
        p = graph->list[i].first;
        while(p){
            q = p->ivex == i ? p->ilink : p->jlink;
            if(p->ivex == i)
                free(p);
            p = q;
        }
    }
    free(graph);
    return OK;
}
//复制图
Status AdjMultilistGraphCopy(AdjMultilistGraph** to, AdjMultilistGraph* from){
    if(!from)
        return ERROR;
    AdjMultilistGraphDestroy(*to);//如果原先有空间，先释放
    *to = (AdjMultilistGraph*)malloc(sizeof(AdjMultilistGraph));
    if(!*to)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*to)->numEdges = from->numEdges;
    (*to)->numVertexes = from->numVertexes;
    //更新顶点结点
    int size = from->numVertexes;
    for(int i = 0; i < size; i++){
        (*to)->list[i].data = from->list[i].data;
        (*to)->list[i].first = NULL;//初始化边表的头指针
    }
    //更新边结点
    //先把被复制图中边结点的标记设为0（未读）
    for(int i = 0; i < size; i++){
        AdjMultilistEdgeNode* p = from->list[i].first;
        while(p){
            p->mark = 0;
            p = p->ivex == i ? p->ilink : p->jlink;
        }
    }
    //更新
    for(int i = 0; i < size; i++){
        AdjMultilistEdgeNode* p = from->list[i].first;
        while(p){
            //如果没有创建该结点，即mark == 0
            if(p->mark == 0){
                //设置p的标记为1（已读）
                p->mark = 1;
                //创建新的边结点
                AdjMultilistEdgeNode* newEdgeNode =
                (AdjMultilistEdgeNode*)malloc(sizeof(AdjMultilistEdgeNode));
                if(!newEdgeNode)
                    return OVERFLOW;
                //边结点中的存储下标
                newEdgeNode->ivex = p->ivex;
                newEdgeNode->jvex = p->jvex;
                //边结点中的权值
                newEdgeNode->weight = p->weight;
                //连接边结点（头插法）
                //i
                newEdgeNode->ilink = (*to)->list[p->ivex].first;
                (*to)->list[p->ivex].first = newEdgeNode;
                //j
                newEdgeNode->jlink = (*to)->list[p->jvex].first;
                (*to)->list[p->jvex].first = newEdgeNode;
            }
            //更新指针p
            p = p->ivex == i ? p->ilink : p->jlink;
        }
    }
    return OK;
}
//深度优先遍历
Status AdjMultilistGraphDFS(AdjMultilistGraph* graph){
    if(!graph)
        return ERROR;
    int size = graph->numVertexes;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * size);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < size; i++)
        visit[i] = 0;//初始为没有访问——0
    //设置图中边结点的标记设为0（未读）
    for(int i = 0; i < size; i++){
        AdjMultilistEdgeNode* p = graph->list[i].first;
        while(p){
            p->mark = 0;
            p = p->ivex == i ? p->ilink : p->jlink;
        }
    }
    //开始搜索
    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i])
            _AdjMultilistGraphDFS(graph, visit, i);
    }
    free(visit);
    return OK;
}
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjMultilistGraphDFS(AdjMultilistGraph* graph, int* visit, int idx){
    visit[idx] = 1;//设置为已读
    printf("%d ", graph->list[idx].data);

    AdjMultilistEdgeNode* p = graph->list[idx].first;
    while(p){
        //如果没有“走”过该结点，即mark == 0
        if(p->mark == 0){
            //设置p的标记为1（已读）
            p->mark = 1;
            int next = p->ivex == idx ? p->jvex : p->ivex;
            if(!visit[next])
                _AdjMultilistGraphDFS(graph, visit, next);
        }
        //更新指针p
        p = p->ivex == idx ? p->ilink : p->jlink;
    }
}
//广度优先遍历
Status AdjMultilistGraphHFS(AdjMultilistGraph* graph){
    if(!graph)
        return ERROR;
    int size = graph->numVertexes;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * size);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < size; i++)
        visit[i] = 0;//初始为没有访问——0
    //设置图中边结点的标记设为0（未读）
    for(int i = 0; i < size; i++){
        AdjMultilistEdgeNode* p = graph->list[i].first;
        while(p){
            p->mark = 0;
            p = p->ivex == i ? p->ilink : p->jlink;
        }
    }
    //创建临时队列，元素个数最多有顶点个数个
    int* queue = (ElemType*)malloc(sizeof(ElemType) * size);
    if(!queue)
        return OVERFLOW;
    int f = 0, t = 0;//队首队尾

    for(int i = 0; i < size; i++){
        if(!visit[i]){
            f = t = 0;//队伍初始化
            visit[i] = 1;
            printf("%d ", graph->list[i].data);//打印当前顶点
            queue[t++] = i;//入队
            while(f != t){//当队列有元素时
                int idx = queue[f++];//出队
                AdjMultilistEdgeNode* p = graph->list[idx].first;
                while(p){
                    //如果没有“走”过该结点，即mark == 0
                    if(p->mark == 0){
                        //设置p的标记为1（已读）
                        p->mark = 1;
                        int next = p->ivex == idx ? p->jvex : p->ivex;
                        if(!visit[next]){
                            visit[next] = 1;//设置已读
                            printf("%d ", graph->list[next].data);//打印当前顶点
                            queue[t++] = next;//入队
                        }
                    }
                    //更新指针p
                    p = p->ivex == idx ? p->ilink : p->jlink;
                }
            }
        }
    }
    free(visit);
    return OK;
}
