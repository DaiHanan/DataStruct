#include "AdjListGraph.h"

//动态创建图
Status AdjListGraphCreate(AdjListGraph** graph){
    if(!graph)
        return ERROR;
    AdjListGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (AdjListGraph*)malloc(sizeof(AdjListGraph));
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
        AdjListEdgeNode* newEdgeNode = (AdjListEdgeNode*)malloc(sizeof(AdjListEdgeNode));
        if(!newEdgeNode)
            return OVERFLOW;
        //边结点中的存储下标
        newEdgeNode->adjvex = to;
        //边结点中的权值
        scanf("%d", &newEdgeNode->weight);
        //连接边结点（头插法）
        newEdgeNode->next = (*graph)->list[from].first;
        (*graph)->list[from].first = newEdgeNode;
    }
    return OK;
}
//利用数组创建图，方便测试
Status AdjListGraphCreateByNums(AdjListGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize){
    if(!graph)
        return ERROR;
    AdjListGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (AdjListGraph*)malloc(sizeof(AdjListGraph));
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
    //更新边结点
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j) continue;//没有指向自身的边
            if(*(arc + i * size + j) != INT_MAX){//邻接矩阵中该点有权值时
                //创建新的边结点
                AdjListEdgeNode* newEdgeNode = (AdjListEdgeNode*)malloc(sizeof(AdjListEdgeNode));
                if(!newEdgeNode)
                    return OVERFLOW;
                //边结点中的存储下标
                newEdgeNode->adjvex = j;
                //边结点中的权值
                newEdgeNode->weight = *(arc + i * size + j);
                //连接边结点（头插法）
                newEdgeNode->next = (*graph)->list[i].first;
                (*graph)->list[i].first = newEdgeNode;
            }
        }
    }
    return OK;
}
//销毁图
Status AdjListGraphDestroy(AdjListGraph* graph){
    if(!graph)
        return ERROR;
    //临时边结点指针
    AdjListEdgeNode* p, * q;
    for(int i = 0; i < graph->numVertexes; i++){
        p = graph->list[i].first;//每个结点的边表的头指针
        //释放所有边结点
        while(p){
            q = p->next;
            free(p);
            p = q;
        }
    }
    free(graph);//释放图
    return OK;
}
//复制图
Status AdjListGraphCopy(AdjListGraph** to, const AdjListGraph* from){
    if(!from)
        return ERROR;
    AdjListGraphDestroy(*to);//如果原先有空间，先释放
    *to = (AdjListGraph*)malloc(sizeof(AdjListGraph));
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
    for(int i = 0; i < size; i++){
        AdjListEdgeNode* p = from->list[i].first;
        while(p){
            //创建新的边结点
            AdjListEdgeNode* newEdgeNode = (AdjListEdgeNode*)malloc(sizeof(AdjListEdgeNode));
            if(!newEdgeNode)
                return OVERFLOW;
            //边结点中的存储下标
            newEdgeNode->adjvex = p->adjvex;
            //边结点中的权值
            newEdgeNode->weight = p->weight;
            //连接边结点（头插法）
            newEdgeNode->next = (*to)->list[i].first;
            (*to)->list[i].first = newEdgeNode;

            //更新指针p
            p = p->next;
        }
    }
    return OK;
}
//深度优先遍历
Status AdjListGraphDFS(const AdjListGraph* graph){
    if(!graph)
        return ERROR;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * graph->numVertexes);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < graph->numVertexes; i++)
        visit[i] = 0;//初始为没有访问——0

    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i])
            _AdjListGraphDFS(graph, visit, i);
    }
    free(visit);
    return OK;
}
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjListGraphDFS(const AdjListGraph* graph, int* visit, int idx){
    visit[idx] = 1;//设置为已读
    printf("%d ", graph->list[idx].data);

    AdjListEdgeNode* p = graph->list[idx].first;
    while(p){
        if(!visit[p->adjvex])//该边存在且对应顶点没有读过
            _AdjListGraphDFS(graph, visit, p->adjvex);//递归
        //更新指针p
        p = p->next;
    }
}
//广度优先遍历
Status AdjListGraphHFS(const AdjListGraph* graph){
    if(!graph)
        return ERROR;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * graph->numVertexes);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < graph->numVertexes; i++)
        visit[i] = 0;//初始为没有访问——0

    //创建临时队列，元素个数最多有顶点个数个
    int* queue = (ElemType*)malloc(sizeof(ElemType) * graph->numVertexes);
    if(!queue)
        return OVERFLOW;
    int f = 0, t = 0;//队首队尾

    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i]){
            f = t = 0;//队伍初始化
            visit[i] = 1;
            printf("%d ", graph->list[i].data);//打印当前顶点
            queue[t++] = i;//入队
            while(f != t){//当队列有元素时
                int idx = queue[f++];//出队
                AdjListEdgeNode* p = graph->list[idx].first;
                while(p){
                    if(!visit[p->adjvex]){
                        visit[p->adjvex] = 1;//设置已读
                        printf("%d ", graph->list[p->adjvex].data);//打印当前顶点
                        queue[t++] = p->adjvex;//入队
                    }
                    p = p->next;
                }
            }
        }
    }
    free(visit);
    return OK;
}

//有向图的拓扑排序
Status AdjListGraphTopologicalSort(const AdjListGraph* graph){
    if(!graph)
        return ERROR;
    //获得入度数组
    int* inDegree = _AdjListGraphTopologicalSort(graph);
    //建立顶点下标临时栈
    int stack[MAXSIZE] = {0};
    int h = -1;
    //所有入度为0的顶点下标入栈
    for(int i = 0; i < graph->numVertexes; i++)
        if(inDegree[i] == 0)
            stack[++h] = i;
    //当栈未空时打印拓扑排序
    int count = 0;//计数器
    while(h != -1){
        //获得栈顶元素(下标)并打印
        int idx = stack[h--];
        printf("%d ", graph->list[idx].data);
        count++;
        //刷新入度
        AdjListEdgeNode* p = graph->list[idx].first;
        while(p){
            if(--inDegree[p->adjvex] == 0)
                stack[++h] = p->adjvex;
            p = p->next;
        }
    }
    free(inDegree);
    if(count < graph->numVertexes)
        printf("该图有回路！");
    return OK;

}
//有向图的拓扑排序 子函数 求每个顶点的入度
int* _AdjListGraphTopologicalSort(const AdjListGraph* graph){
    int size = graph->numVertexes;
    //申请入度数组
    int* inDegree = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        inDegree[i] = 0;
    //累计入度
    for(int i = 0; i < size; i++){
        //临时指针指向该顶点第一个邻接边
        AdjListEdgeNode* p = graph->list[i].first;
        while(p){
            inDegree[p->adjvex]++;
            p = p->next;
        }
    }
    //返回入度数组
    return inDegree;
}

//有向图的关键路径
Status AdjListGraphCriticalPath(const AdjListGraph* graph){
    int rStack[MAXSIZE] = {0};//拓扑逆向栈
    int ve[MAXSIZE] = {0};//最早发生时间

    if(_AdjListGraphCriticalPath(graph, rStack, ve) != OK)
        return ERROR;
    //初始化最迟发生时间
    int vl[MAXSIZE];
    for(int i = 0; i < graph->numVertexes; i++)
        vl[i] = ve[graph->numVertexes - 1];
    //获得最迟发生时间
    int h = graph->numVertexes - 1;
    while(h != -1){
        //获得栈顶元素
        int idx = rStack[h--];
        //扫描其所有边并更新最迟发生时间
        AdjListEdgeNode* p = graph->list[idx].first;
        while(p){
            if(vl[p->adjvex] - p->weight < vl[idx] )
                vl[idx] = vl[p->adjvex] - p->weight;

            p = p->next;
        }
    }
    //打印关键路径
    for(int i = 0; i < graph->numVertexes; i++){
        for(AdjListEdgeNode* p = graph->list[i].first; p; p = p->next){
            int k = p->adjvex, weight = p->weight;
            int ee = ve[i];
            int el = vl[k] - weight;
            if(ee == el)
                printf("%d → %d\n", graph->list[i].data, graph->list[k].data);
        }
    }
    return OK;
}
//有向图的关键路径 子函数 拓扑排序修改版 rStack为拓扑逆向栈，ve为事件最早发生时间
Status _AdjListGraphCriticalPath(const AdjListGraph* graph, int rStack[], EdgeType ve[]){
    if(!graph)
        return ERROR;
    //获得入度数组
    int* inDegree = _AdjListGraphTopologicalSort(graph);
    //建立顶点下标临时栈
    int stack[MAXSIZE] = {0};
    int h = -1;
    //所有入度为0的顶点下标入栈
    for(int i = 0; i < graph->numVertexes; i++)
        if(inDegree[i] == 0)
            stack[++h] = i;
    //当栈未空时打印拓扑排序
    int count = 0;//计数器
    while(h != -1){
        //获得栈顶元素(下标)并入逆向栈
        int idx = stack[h--];
        rStack[count++] = idx;
        //刷新入度
        AdjListEdgeNode* p = graph->list[idx].first;
        while(p){
            if(--inDegree[p->adjvex] == 0){
                stack[++h] = p->adjvex;
            }
            //更新最早发生时间
            if(ve[idx] + p->weight > ve[p->adjvex])
                ve[p->adjvex] = ve[idx] + p->weight;

            p = p->next;
        }
    }
    free(inDegree);
    if(count < graph->numVertexes)
        return ERROR;//有回路
    return OK;
}
